#include <iostream>
#include <cmath>
#include "header.h"

int main() {
    double lat1 = 40.7128, lon1 = -74.0060;
    double lat2 = 51.5074, lon2 = -0.1278;

    double distance = haversineDistance(lat1, lon1, lat2, lon2);
    
    std::cout << "Distance: " << distance << " km" << std::endl;
    return 0;
}
