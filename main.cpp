//-------------------------Libraries-------------------------
#include <iostream> //Main setup
#include <cmath> //Math library for calculations
#include "header.h" //Including a header
#include "class.h" //Class definitions
#include "FS.h" //Basic file inclusion library
//Compass Libraries
#include <Adafruit_BNO055.h> //Library for the main compass. It recieves vectors from the compass of the direction relative to absolute north
#include <Adafruit_Sensor.h> //Base library for adafruit sensors
#include <Wire.h> //ESP-32 Library to handle communication
//GPS Libraries
#include <TinyGPS++.h> //Library for the main GPS - Processes latitude, longitude, and all the math
#include <HardwareSerial.h> //Establishes communication between the GPS and the ESP32
//Servo Libraries
#include <ESP32Servo.h> //Provides angle control for the servo motor
//Local Data Libraries (Bus stops)
#include <LittleFS.h> //Allows the ESP32 to read the boulder bus stop data
#include <Preferences.h> //Calibration library for the ESP32 with the compass
//Output and Control Libraries
#include <driver/ledc.h> //Generates tones for the pizzo buzzer
#include <Arduino.h> //Basic Arduino Library for all the arduino commands


//-------------------------Main-------------------------


TinyGPSPlus gps; //Initializes and defines the gps
HardwareSerial gpsSerial(2); //Initializes the serial output for the gps

void setup() //Initialization for the code. Defining Variables
{
    Serial.begin(115200); //set baud rate


    
    delay(500);//wait
}

void loop() //Main body of the code
{
    analogRead;
    delay(1000);//delay for next loop
}

