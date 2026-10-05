//Libraries
#include <iostream> //Main setup
#include <cmath> //Math library for calculations
#include "header.h" //Including a header
//Compass Libraries
#include <Adafruit_BNO055.h> //Library for the main compass. It recieves vectors from the compass of the direction relative to absolute north
#include <Adafruit_Sensor.h> //Base library for adafruit sensors
#include <Wire.h> //ESP-32 Library to handle communication
//GPS Libraries


void setup() //Initialization for the code. Defining Variables
{
    
}

void loop() //Main body of the code
{

}



int main() //Formula to calculate the distance between two points (I think)
{
    double lat1 = 40.7128, lon1 = -74.0060;
    double lat2 = 51.5074, lon2 = -0.1278;

    double distance = haversineDistance(lat1, lon1, lat2, lon2);
    
    std::cout << "Distance: " << distance << " km" << std::endl;
    return 0;
}
