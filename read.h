#ifndef READ_H
#define READ_H

#include <Arduino.h>
#include <TinyGPS++.h>
#include "BusStops.h"
#include "NavUtils.h"

// Reference to global GPS object from TinyGPS++
extern TinyGPSPlus gps;

// Function to get the user's current latitude from GPS
inline double getLatitude() 
{
    if (gps.location.isValid()) 
    {
        return gps.location.lat();
    }
    else
    {
        return 0.0; // Return 0.0 if no satellite fix
    } 
}

// Function to get the user's current longitude from GPS
inline double getLongitude() 
{
    if (gps.location.isValid()) 
    {
        return gps.location.lng();
    }
    else
    {
        return 0.0; // Return 0.0 if no satellite fix
    }
}

// Function to scan all 7,516 bus stops and return the bearing angle to the nearest stop
inline double readBusData()
{
    double userLat = getLatitude();
    double userLng = getLongitude();
    
    // Check if valid GPS coordinates are available
    if (userLat == 0.0 && userLng == 0.0) 
    {
        Serial.println("GPS fix not available yet.");
        return -1.0; 
    }

    double closestDistance = 1e12; // High initial value for comparison
    double bearing = 0.0;          // Bearing angle to nearest stop

    for (int i = 0; i < TOTAL_BUS_STOPS; i++)
    {
        double busLat = busStops[i].lat;
        double busLng = busStops[i].lng;
        
        double dist = haversineDistance(userLat, userLng, busLat, busLng);
        if (dist < closestDistance)
        {
            closestDistance = dist;
            bearing = bearingAngle(userLat, userLng, busLat, busLng);
        }
    }
    
    return bearing; // Returns bearing angle (in radians) to nearest stop
}

#endif // READ_H
