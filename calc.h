#ifndef NAV_UTILS_H
#define NAV_UTILS_H

#include <Arduino.h>

// Useful constants for program
const double RAD_EARTH_BOULDER = 6370964.362946211; // Earth radius in Boulder meters

// Convert Degrees to Radians
inline double degreeToRad(double degree) 
{ 
    return degree * PI / 180.0;
}

// Convert Radians to Degrees
inline double radToDegree(double rad) 
{ 
    return rad * 180.0 / PI;
}

double haversineDistance(double lat1, double lon1, double lat2, double lon2) //Calculate distance on a sphere from point (lat1,lon1) to (lat2,lon2) using Haversine formula 
{
    //Assume latitude and longitude are in Degrees, delta Latitude and Longitude converted to Radians
    double dLat = degreeToRad(lat2 - lat1);
    double dLon = degreeToRad(lon2 - lon1); 
    
    //Assume latitude and longitude are in Degrees, Latitude converted to Radians
    lat1 = degreeToRad(lat1);
    lat2 = degreeToRad(lat2);

    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    
    return abs(rad_Earth_Boulder * c);
}

double centralAngleBetweenLon(double lat1, double lon1, double lat2, double lon2) //Longitude of angle from one position(lat1,lon1) to another(lat2,lon2) on a sphere
{
    //Assume latitude and longitude are in Degrees, convert to radians
    lon1 = degreeToRad(lon1);
    lon2 = degreeToRad(lon2);
    
    double dLon = abs(lon1-lon2); //lon

    return dLon;
}

double centralAngleBetweenLat(double lat1, double lon1, double lat2, double lon2)  //Latidinual of angle from one position(lat1,lon1) to another(lat2,lon2) on a sphere
{
    //Assume latitude and longitude are in Degrees, convert to radians
    lat1 = degreeToRad(lat1);
    lat2 = degreeToRad(lat2);
    lon1 = degreeToRad(lon1);
    lon2 = degreeToRad(lon2);
    
    double dLat = acos(cos(lat1) * cos(lat2) + sin(lat1) * sin(lat2) * cos(lon1-lon2)); //lat
    return dLat;
}

// Calculate bearing angle between user and destination (returns radians from 0 to 2*PI)
inline double bearingAngle(double latUser, double lonUser, double latStop, double lonStop) 
{
    // Convert all inputs to radians
    double newlatUser = degreeToRad(latUser);
    double newlonUser = degreeToRad(lonUser);
    double newlatStop = degreeToRad(latStop);
    double newlonStop = degreeToRad(lonStop);

    double dLon = newlonStop - newlonUser; // Destination minus Origin

    double x = cos(newlatStop) * sin(dLon);
    double y = cos(newlatUser) * sin(newlatStop) - 
               sin(newlatUser) * cos(newlatStop) * cos(dLon);

    double bearing = atan2(x, y);
    
    // Normalize to 0 to 2*PI radians
    if (bearing < 0) {
        bearing += 2.0 * PI;
    }
    return bearing; 
}

#endif // NAV_UTILS_H
