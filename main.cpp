#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <ESP32Servo.h>
#include <HardwareSerial.h>
#include <LittleFS.h>
#include <TinyGPS++.h>
#include <WiFi.h>
#include <climits>
#include <esp_bt.h>
#include "NavUtils.h"
#include "read.h"
#include "buzzer.h"

// Global Instances
Adafruit_BNO055 bno = Adafruit_BNO055(55);
Servo pointerServo;
TinyGPSPlus gps;
HardwareSerial GPSSerial(1); // Port 1

// Pin & Calibration Definitions
const int servoPin = 13;
const float servoMin = 20.0;
const float servoMax = 140.0;
const float servoRange = 120.0;
const float gearRatio = 3.0;

float targetServoAngle = 80.0;
double busLat = 0.0;
double busLng = 0.0;
double userLat = 0.0;
double userLng = 0.0;

const int buzzerPin = 12;

#define GPS_RX 38      // Feather pin labeled 'RX'
#define GPS_TX 39      // Feather pin labeled 'TX'
#define GPS_BAUD 9600  // Default factory baud for ATGM336H

void setup() {
  // Disable radios immediately to save power/reduce noise
  WiFi.mode(WIFI_OFF);
  btStop();
  
  pinMode(buzzerPin, OUTPUT);
  startTone(buzzerPin);

  Serial.begin(115200);

  // Power stabilization delay to protect the GPS startup cycle
  delay(2000);
  Serial.println("Orientation Sensor Test");
  
  pointerServo.attach(servoPin);
  
  if (!bno.begin()) {

    Serial.println("No BNO055 detected. Check wiring!");
    badTone(buzzerPin);
    while (1);
  }
  
  delay(1000);
  bno.setExtCrystalUse(true);
  
  // Start with the pointer aimed north
  pointerServo.write((int)targetServoAngle);
  
  Serial.println("--- ATGM336H GPS Reader Initializing ---");
  // Force HardwareSerial to point to pins 38 and 39
  GPSSerial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX, GPS_TX);
  Serial.println("Listening for GPS data...");
}

void loop() {
  // Feed incoming characters from the GPS module into the TinyGPS++ parser
  // (Crucial: Must run continuously without delay blocks to avoid serial buffer overflow)
  while (GPSSerial.available() > 0) {
    char c = GPSSerial.read();
    gps.encode(c);
  }

  // Non-blocking Timer for Diagnostics & Servo Control (Every 5 seconds)
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 5000) {
    lastUpdate = millis();
    
    Serial.print("Diagnostic - Total Characters Processed: ");
    Serial.println(gps.charsProcessed());
    
    if (gps.location.isValid()) {
      goodTone(buzzerPin);
      //servo angles to bus stopeth
      userLat = gps.location.lat();
      userLng = gps.location.lng();

      targetServoAngle = readBusData(&userLat, &userLng, &busLat, &busLng);
      
      proximityTone(buzzerPin, haversineDistance(userLat, userLng, busLat, busLng));
      
      
      Serial.print("LATITUDE: ");   Serial.println(gps.location.lat(), 6);
      Serial.print("LONGITUDE: ");  Serial.println(gps.location.lng(), 6);
      Serial.print("SATELLITES: "); Serial.println(gps.satellites.value());
    } else {
      Serial.println("Waiting for Satellite Lock... (Take the antenna near a window or outside)");
      badTone(buzzerPin);
    }
    
    // Hardware Failure Check
    if (gps.charsProcessed() < 10) {
      Serial.println("ERROR: No GPS data received. Check RX/TX wiring pins!");
      badTone(buzzerPin);
    }
    
    Serial.println("---------------------------------------");
    
  }

  // Non-blocking Compass Tracking & Servo Control (Every 100ms)
  static unsigned long lastServoMove = 0;
  if (millis() - lastServoMove > 100) {
    lastServoMove = millis();
    
    sensors_event_t event;
    bno.getEvent(&event);
    float heading = event.orientation.x;
    
    // Normalize heading to 0–360 degrees
    heading = fmod(heading, 360.0);
    if (heading < 0.0) {
      heading += 360.0;
    } 
    
    // Reverse servo direction to compensate for the gears.
    // The 3:1 ratio means 1 degree of servo movement produces 3 degrees of pointer movement.
    float servoAngle = targetServoAngle + heading / gearRatio;
    
    // Wrap the servo command into its allowed 120-degree range.
    while (servoAngle < servoMin) {
      servoAngle += servoRange;
    }
    while (servoAngle > servoMax) {
      servoAngle -= servoRange;
    }
    
    int targetAngle = constrain((int)round(servoAngle), (int)servoMin, (int)servoMax);
    pointerServo.write(targetAngle);
    
    Serial.print("Compass heading: ");
    Serial.print(heading);
    Serial.print(" | Servo target: ");
    Serial.println(targetAngle);
  }
}
