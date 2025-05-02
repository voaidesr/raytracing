#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vec3.h"
#include "interval.h"

using color = vec3;

double linear_to_gamma(double linear_component);

void write_color(std::ostream& out, const color& pixel_color);

#endif