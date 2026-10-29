#include "BusStops.h"

// Reference to global GPS object from TinyGPS++
extern TinyGPSPlus gps;

// Function to get the user's current latitude from GPS
double getLatitude() 
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
double getLongitude() 
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
double readBusData(double *userLat, double *userLng, double *busLat, double *busLng)
{   
    // Check if valid GPS coordinates are available
    if (*userLat == 0.0 && *userLng == 0.0) 
    {
        Serial.println("GPS fix not available yet.");
        return -1.0; 
    }

    double closestDistance = 1e12; // High initial value for comparison
    double bearing = 0.0;          // Bearing angle to nearest stop

    for (int i = 0; i < TOTAL_BUS_STOPS; i++)
    {
        double busLatTemp = busStops[i].lat;
        double busLngTemp = busStops[i].lng;
        
        double dist = haversineDistance(*userLat, *userLng, busLatTemp, busLngTemp);
        if (dist < closestDistance)
        {
            *busLat = busStops[i].lat;
            *busLng = busStops[i].lng;
            closestDistance = dist;
            bearing = bearingAngle(*userLat, *userLng, *busLat, *busLng);
        }
    }
    
    return bearing; // Returns bearing angle (in radians) to nearest stop
}
