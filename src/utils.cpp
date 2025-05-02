#include "utils.h"

double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0); // [0, 1)
    static std::mt19937 generator(std::random_device{}());
    return distribution(generator);
}

double random_double(double min, double max) {
    return min + (max - min) * random_double(); // [min, max)
}