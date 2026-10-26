//-------------------------Libraries-------------------------
#include <iostream> //Main setup
#include <cmath> //Math library for calculations
#include "calc.h" //Including a header
#include "read.h" //Class definitions
#include "FS.h" //Basic file inclusion library
//Compass Libraries
#include <Adafruit_BNO055.h> //Library for the main compass. It recieves vectors from the compass of the direction relative to absolute north
#include <Adafruit_Sensor.h> //Base library for adafruit sensors
#include <Wire.h> //ESP-32 Library to handle communication
//GPS Libraries
#include <TinyGPS++.h> //Library for the main GPS - Processes latitude, longitude, and all the math
#include <SoftwareSerial.h> //Emulates serial ports for serial conections
#include <HardwareSerial.h> //Establishes communication between the GPS and the ESP32
//Servo Libraries
#include <ESP32Servo.h> //Provides angle control for the servo motor
//Local Data Libraries (Bus stops)
#include <LittleFS.h> //Allows the ESP32 to read the boulder bus stop data
#include <Preferences.h> //Calibration library for the ESP32 with the compass
//Output and Control Libraries
#include <driver/ledc.h> //Generates tones for the pizzo buzzer
#include <Arduino.h> //Basic Arduino Library for all the arduino commands
#include <utility/imumaths.h> //for compass
#include <ESP32Servo.h>//servo library for esp32

//-------------------------Main-------------------------


TinyGPSPlus gps; //Initializes and defines the gps
HardwareSerial gpsSerial(2); //Initializes the serial output for the gps
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);
Servo pointerServo;

const int servoPin = 13;

// Tracking position and timing
float currentServoAngle = 0.0; 
float lastHeading = 0.0;
unsigned long lastTime = 0;

void setup() {
  Serial.begin(9600);
  pointerServo.attach(servoPin);

  if(!bno.begin()) {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);

  // Initialize starting positions
  sensors_event_t event;
  bno.getEvent(&event);
  lastHeading = event.orientation.x;
  lastTime = millis();
}

void loop(void) {
  sensors_event_t event;
  bno.getEvent(&event);
  float currentHeading = event.orientation.x;
  unsigned long currentTime = millis();
  
  // Calculate time elapsed in seconds
  float deltaTime = (currentTime - lastTime) / 1000.0;
  
  if (deltaTime > 0.0) {
    // 1. Calculate change in heading (handling the 0/360 wrap safely)
    float headingDiff = currentHeading - lastHeading;
    if (headingDiff > 180.0) {
      headingDiff -= 360.0;
    } else if (headingDiff < -180.0) {
      headingDiff += 360.0;
    }

    // 2. Compass Angular Velocity (degrees per second)
    float compassVelocity = headingDiff / deltaTime;

    // 3. Servo Angular Velocity scaled to 1/3 of the compass speed
    float servoVelocity = compassVelocity / 3.0;

    // 4. Update the servo's absolute position based on its new velocity
    currentServoAngle += servoVelocity * deltaTime;

    // 5. Constrain the servo safely within your physical limits (0 to 120)
    currentServoAngle = constrain(currentServoAngle, 0.0, 120.0);

    // Write the final angle to the servo
    pointerServo.write((int)currentServoAngle);

    // Debugging tracking
    Serial.print("Comp Vel: "); Serial.print(compassVelocity);
    Serial.print(" | Servo Vel: "); Serial.print(servoVelocity);
    Serial.print(" | Servo Pos: "); Serial.println(currentServoAngle);
  }

  // Save values for the next loop iteration
  lastHeading = currentHeading;
  lastTime = currentTime;

  delay(20); // Faster sample rate ensures velocity tracking stays tight
}
