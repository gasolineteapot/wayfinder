
TinyGPSPlus gps; //Initializes and defines the gps
HardwareSerial gpsSerial(2); //Initializes the serial output for the gps

double getLatitude() //Function to get the users current position in latitude
{
    while(gpsSerial.available() > 0) //Reads the serial output from the GPS and looks for new characters
        {
            gps.encode(gps.read()); //The read function reads the gps's characters while the encode function translates it to actual tangible data
        }
    if(gps.location.isUpdated() && gps.location.isValid())  
    {
        double currentLat = gps.location.lat(); //Obtains the users current latitude based off the gps's location
    }
    //The isUpdated method checks to make sure the gps is updated to the users current location. 
    //The isValid method checks to make sure the the gps is able to find a satelite to read off of.
    
    return currentLat; //Returns the current latitude of the user
}

double getLongitude() //Function to get the users current positon in longitude
{
    while(gpsSerial.available() > 0) //Reads the serial output from the GPS and looks for new characters
        {
            gps.encode(gps.read()); //The read function reads the gps's characters while the encode function translates it to actual tangible data
        }
    if(gps.location.isUpdated() && gps.location.isValid())  
    {
        double currentLng = gps.location.lng(); //Obtains the users current longitude based off the gps's location
    }
    //The isUpdated method checks to make sure the gps is updated to the users current location. 
    //The isValid method checks to make sure the the gps is able to find a satelite to read off of.
    
    return currentLng; //Returns the current longitude of the user
}


int readBusData()//Function to read the bus data and returns the closest index of latitude and longitude
{
    File busRoutes = LittleFS.open("/BusStops_Active.csv", "r"); //Defines the file and opens it to read only
    if(!busRoutes) //If there are any problems with reading the file
    {
        Serial.println("Failed to retrieve file contents"); 
        return; //Exit safely
    }

    int i = 0; //Integer to count the number of loops the code reads through
    int k = 0; //Integer to assign the index of the closest latitude and longitude
    double dist = 0.0; //Declaration of the distance
    double userLat = getLatitude(); //From the previous function - gets the users latitude
    double userLng = getLongitude(); //From the previous function - gets the users longitude
    double closestDistance = INT_MAX; //Value to compare the distance
    while(busRoutes.available()) //While the file is open and being read - continuously reads the file until there is nothing left to read
    {
        String lineLat = busRoutes.readStringUntil(","); //Reads the line for latitude until there is a comma seperating them
        String lineLong = busRoutes.readStringUntil('\n'); //Reads the line for longitude until there is a line break seperating them
        lineLat.trim(); //Removes any unecessary white space
        lineLong.trim(); //Removes any unecessary white space

        double readLat = lineLat.toDouble(); //Converts the latitude (which was originaly a string) to a double
        double readLong = lineLong.toDouble(); //Converts the longitude (which was originally a string) to a double

        double dist = haversineDistance(userLat, userLng, readLat, readLong); //Calculates the absolute distance between the two points
        if(dist < closestDistance) //If statement to find the closest distance
        {
            closestDistance = dist; 
            k = i;
        }
        i++;
    }
    return k;

    int j = 0;
    while(busRoutes.available() && j <= k)
        {

        }
    
}


