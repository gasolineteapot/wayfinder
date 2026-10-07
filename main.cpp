//Basic Libraries
#include <iostream> //Main setup
#include <cmath> //Math library for calculations
#include "header.h" //Including a header
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


void setup() //Initialization for the code. Defining Variables
{
    
}

void loop() //Main body of the code
{

}

//Extra Functions to implement in the code
void readBusData()//Function to read the bus data
{
    File busRoutes = LittleFS.open("/BusStops_Active.csv", "r"); //Defines the file and opens it to read only
    if(!busRoutes) //If there are any problems with reading the file
    {
        Serial.println("Failed to retrieve file contents"); 
        return; //Exit safely
    }
    double baseLat = ; //Variable to store latitude that is baesd off the users current position
    double baseLong = ; //Variable to store longitude that is based off the users current position

    while(busRoutes.available()) //While the file is open and being read
    {
        String lineLat = busRoutes.readStringUntil(","); //Reads the line for latitude until there is a comma seperating them
        String lineLong = busRoutes.readStringUntil('\n'); //Reads the line for longitude until there is a line break seperating them
        lineLatitude.trim(); //Removes any unecessary white space
        lineLongitude.trim(); //Removes any unecessary white space

        double readLat = lineLat.toDouble(); //Converts the latitude (which was originaly a string) to a double
        double readLong = lineLong.toDouble(); //Converts the longitude (which was originally a string) to a double
        if(readLat < baseLat)
        {
            baseLat = read
        }
    }
}


