#include <iostream>
#include <cmath>


double degreeToRad(double degree) {
    return degree * M_PI / 180.0;
}

double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    double dLat = degreeToRad(lat2 - lat1);
    double dLon = degreeToRad(lon2 - lon1);

    lat1 = degreeToRad(lat1);
    lat2 = degreeToRad(lat2);


    double a = std::sin(dLat / 2.0) * std::sin(dLat / 2.0) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dLon / 2.0) * std::sin(dLon / 2.0);
               
    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
    
    
    double radius = 6371.0; 
    return radius * c;
}

int main() {
    double lat1 = 40.7128, lon1 = -74.0060;
    double lat2 = 51.5074, lon2 = -0.1278;

    double distance = haversineDistance(lat1, lon1, lat2, lon2);
    
    std::cout << "Distance: " << distance << " km" << std::endl;
    return 0;
}
