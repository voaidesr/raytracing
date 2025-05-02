#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <memory>
#include <vector>
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

using std::shared_ptr;
using std::make_shared;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

double degrees_to_radians(double degrees);

double random_double();

double random_double(double min, double max);

#endif