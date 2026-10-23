
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
    if(gps.location.isUpdated()) 
    {
        return gps.location.lng(); //Obtains the users current longitude based off the gps's location
    }
    else
    {
        return 0.0;
    }
}


double readBusData()//Function to read the bus data and returns the angle between the user and the nearest bus stop
{
    File busRoutes = LittleFS.open("/BusStops_Active.csv", "r"); //Defines the file and opens it to read only
    if(!busRoutes) //If there are any problems with reading the file
    {
        Serial.println("Failed to retrieve file contents"); 
        return -1.0; //Exit safely
    }

    double dist = 0.0; //Declaration of the distance
    double userLat = getLatitude(); //From the previous function - gets the users latitude
    double userLng = getLongitude(); //From the previous function - gets the users longitude
    double closestDistance = INT_MAX; //Value to compare the distance
    double bearing = 0.0; //Value for the central angle to know which way the servo rotates
    const double rad_Earth_Boulder = 6370964.362946211; //Value for the radius of the earth
    while(busRoutes.available()) //While the file is open and being read - continuously reads the file until there is nothing left to read
    {
        String lineLat = busRoutes.readStringUntil(','); //Reads the line for latitude until there is a comma char seperating them
        String lineLong = busRoutes.readStringUntil('\n'); //Reads the line for longitude until there is a line break seperating them
        lineLat.trim(); //Removes any unecessary white space
        lineLong.trim(); //Removes any unecessary white space

        double readLat = lineLat.toDouble(); //Converts the latitude (which was originaly a string) to a double
        double readLong = lineLong.toDouble(); //Converts the longitude (which was originally a string) to a double

        double dist = haversineDistance(userLat, userLng, readLat, readLong); //Calculates the absolute distance between the two points
        if(dist < closestDistance) //If statement to find the closest distance
        {
            closestDistance = dist; 
            bearing = radToDegree(bearingAngle(userLat, userLng, readLat, readLong)); //Function to find the central angle
        }
    }
    return bearing;
}


