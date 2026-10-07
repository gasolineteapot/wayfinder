double degreeToRad(double degree) { //Convert Radians to Degrees
    return degree * M_PI / 180.0;
}

double haversineDistance(double lat1, double lon1, double lat2, double lon2) //Calculate distance on a sphere from point (lat1,lon1) to (lat2,lon2) using Haversine formula
{
    double dLat = degreeToRad(lat2 - lat1);
    double dLon = degreeToRad(lon2 - lon1); 

    lat1 = degreeToRad(lat1);
    lat2 = degreeToRad(lat2);

    double a = std::sin(dLat / 2.0) * std::sin(dLat / 2.0) + std::cos(lat1) * std::cos(lat2) * std::sin(dLon / 2.0) * std::sin(dLon / 2.0);
    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
    
    
    double radius = 6371.0; 
    return radius * c;
}
