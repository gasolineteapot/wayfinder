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
int servoPin = 13; 


void setup() {
  Serial.begin(9600); // Initialize Serial Monitor at 9600 bps

  pointerServo.attach(servoPin);

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);
  
  int servoAngle;

    if (event.orientation.x >= 290.0 && event.orientation.x <= 360.0)
    {
        servoAngle = (int)(event.orientation.x - 290.0);
        pointerServo.write(constrain(servoAngle, 0, 60));
    }
    else if (event.orientation.x >= 0.0 && event.orientation.x <= 70.0)
    {
        servoAngle = (int)(event.orientation.x + 60.0);
        pointerServo.write(constrain(servoAngle, 60, 120));
    }
    else{
        pointerServo.write(constrain(servoAngle, 60, 120));
    }

  Serial.println(event.orientation.x);
  
  delay(100);
}
