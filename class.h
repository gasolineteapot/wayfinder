
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

double compareLatitude(double lat) //Function to compare the busRoute distances and find the closest route to the user - returns the closest latitude
{
    
}

double compareLongitude(double lng) //Function to compare the busRoute distances and find the closest route to the user - returns the closest longitude
{

}

double readBusDataLAT()//Function to read the bus data
{
    File busRoutes = LittleFS.open("/BusStops_Active.csv", "r"); //Defines the file and opens it to read only
    if(!busRoutes) //If there are any problems with reading the file
    {
        Serial.println("Failed to retrieve file contents"); 
        return; //Exit safely
    }

    while(busRoutes.available()) //While the file is open and being read - continuously reads the file until there is nothing left to read
    {
        String lineLat = busRoutes.readStringUntil(","); //Reads the line for latitude until there is a comma seperating them
        String lineLong = busRoutes.readStringUntil('\n'); //Reads the line for longitude until there is a line break seperating them
        lineLatitude.trim(); //Removes any unecessary white space
        lineLongitude.trim(); //Removes any unecessary white space

        double readLat = lineLat.toDouble(); //Converts the latitude (which was originaly a string) to a double
        double readLong = lineLong.toDouble(); //Converts the longitude (which was originally a string) to a double
    }
}
