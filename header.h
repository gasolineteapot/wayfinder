//useful constants for program
const double RAD_EARTH_BOULDER = 6370964.362946211;


//Functions for Wayfinder
double degreeToRad(double degree) { //Convert Degrees to Radians
    return degree * M_PI / 180.0;
}

double radToDegree(double rad){ //Convert Radian to Degrees
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
    
    
    double radius = 6371.0; 
    return radius * c;
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

double angleBetweenTwoOnSurface(double lat1, double lon1, double lat2, double lon2, double radius){ //Imagining the central angle projecting dX and dY onto the surface of a sphere as a triangle, this is the upper angle near the dY side 
    return std::atan((std::sin(centralAngleBetweenLat(lat1,lon1,lat2,lon2))*radius)/(std::sin(centralAngleBetweenLon(lat1,lon1,lat2,lon2))*radius));
}
