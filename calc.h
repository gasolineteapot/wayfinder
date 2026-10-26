//useful constants for program
const double rad_Earth_Boulder = 6370964.362946211;


//Functions for Wayfinder
double degreeToRad(double degree) //Convert Degrees to Radians
{ 
    return degree * M_PI / 180.0;
}

double radToDegree(double rad) //Convert Radian to Degrees
{ 
    return rad * 180.0 / M_PI;
}

double haversineDistance(double lat1, double lon1, double lat2, double lon2) //Calculate distance on a sphere from point (lat1,lon1) to (lat2,lon2) using Haversine formula 
{
    //Assume latitude and longitude are in Degrees, delta Latitude and Longitude converted to Radians
    double dLat = degreeToRad(lat2 - lat1);
    double dLon = degreeToRad(lon2 - lon1); 
    
    //Assume latitude and longitude are in Degrees, Latitude converted to Radians
    lat1 = degreeToRad(lat1);
    lat2 = degreeToRad(lat2);

    double a = std::sin(dLat / 2.0) * std::sin(dLat / 2.0) + std::cos(lat1) * std::cos(lat2) * std::sin(dLon / 2.0) * std::sin(dLon / 2.0);
    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
    
    return std::abs(rad_Earth_Boulder * c);
}

double centralAngleBetweenLon(double lat1, double lon1, double lat2, double lon2) //Longitude of angle from one position(lat1,lon1) to another(lat2,lon2) on a sphere
{
    //Assume latitude and longitude are in Degrees, convert to radians
    lon1 = degreeToRad(lon1);
    lon2 = degreeToRad(lon2);
    
    double dLon = std::abs(lon1-lon2); //lon

    return dLon;
}

double centralAngleBetweenLat(double lat1, double lon1, double lat2, double lon2)  //Latidinual of angle from one position(lat1,lon1) to another(lat2,lon2) on a sphere
{
    //Assume latitude and longitude are in Degrees, convert to radians
    lat1 = degreeToRad(lat1);
    lat2 = degreeToRad(lat2);
    lon1 = degreeToRad(lon1);
    lon2 = degreeToRad(lon2);
    
    double dLat = std::acos(std::cos(lat1)*std::cos(lat2)+std::sin(lat1)*std::sin(lat2)*std::cos(lon1-lon2)); //lat
    return dLat;
}
//Functions for Wayfinder
double degreeToRad(double degree) //Convert Degrees to Radians
{ 
    return degree * M_PI / 180.0;
}

double radToDegree(double rad) //Convert Radian to Degrees
{ 
    return rad * 180.0 / M_PI;
}

double bearingAngle(double latUser, double lonUser, double latStop, double lonStop) 
{
    // Convert all inputs to radians
    latUser = degreeToRad(latUser);
    lonUser = degreeToRad(lonUser);
    latStop = degreeToRad(latStop);
    lonStop = degreeToRad(lonStop);

    double dLon = lonStop - lonUser; // Destination minus Origin

    double x = std::cos(latStop) * std::sin(dLon);
    double y = std::cos(latUser) * std::sin(latStop) - 
               std::sin(latUser) * std::cos(latStop) * std::cos(dLon);

    double bearing = std::atan2(x, y);
    
    // Normalize to 0 to 2*M_PI radians (0 to 360 degrees) if desired
    if (bearing < 0) {
        bearing += 2.0 * M_PI;
    }
    return bearing; 
}

