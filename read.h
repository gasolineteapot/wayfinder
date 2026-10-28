
double getLatitude() //Function to get the users current position in latitude
{
    if(gps.location.isValid())  //Checks to make sure that there is a satelite to use
    {
        return gps.location.lat(); //Obtains the users current latitude based off the gps's location
    }
    else
    {
        return 0.0; //If no satelite is found
    } 
}

double getLongitude() //Function to get the users current positon in longitude
{
    if(gps.location.isValid()) 
    {
        return gps.location.lng(); //Obtains the users current longitude based off the gps's location
    }
    else
    {
        return 0.0; //If no satelite is found
    }
}


double readBusData()//Function to read the bus data and returns the angle between the user and the nearest bus stop
{

        
    double dist = 0.0; //Declaration of the distance
    double userLat = getLatitude(); //From the previous function - gets the users latitude
    double userLng = getLongitude(); //From the previous function - gets the users longitude
    double busLat = 0.0; //Initializes the bus stop latitude
    double busLng = 0.0; //Initializes the bus stop longitude
    double closestDistance = INT_MAX; //Value to compare the distance
    double bearing = 0.0; //Value for the central angle to know which way the servo rotates
    const double rad_Earth_Boulder = 6370964.362946211; //Value for the radius of the earth
    
    if (userLat == 0.0 && userLng == 0.0) 
    {
        Serial.println("GPS fix not available yet.");
        return -1.0; 
    }

    for(int i = 0; i <= sizeof(busStops); i++)
    {
        dist = haversineDistance(userLat, userLng, busLat, busLng);
    }
    if(dist < closestDistance)
    {
        closestDistance = dist;
    }
    return bearing;
}


