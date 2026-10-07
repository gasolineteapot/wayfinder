//Functions for Wayfinder
double degreeToRad(double degree) { //Convert Radians to Degrees
    return degree * M_PI / 180.0;
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


double centralAngleBetweenLon(double lat1, double lon1, double lat2, double lon2) //Central angle from one position(lat1,lon1) to another(lat2,lon2) on a sphere
{
    //Assume latitude and longitude are in Degrees, convert to radians
    lon1 = degreeToRad(lon1);
    lon2 = degreeToRad(lon2);
    
    dLon = std::abs(lon1-lon2); //lon

    return dLon;
}

double centralAngleBetweenLat(double lat1, double lon1, double lat2, double lon2)
{
    //Assume latitude and longitude are in Degrees, convert to radians
    lat1 = degreeToRad(lat1);
    lat2 = degreeToRad(lat2);
    lon1 = degreeToRad(lon1);
    lon2 = degreeToRad(lon2);
    
    dLat = std::arccos(std::cos(lat1)*std::cos(lat2)+std::sin(lat1)*std::sin(lat2)*std::cos(lon1-lon2)); //lat
    return dLat;
}
