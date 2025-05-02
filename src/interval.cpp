#include "utils.h"

interval::interval() : min(+infinity), max(-infinity) {}
interval::interval(double min, double max) : min(min), max(max) {}

double interval::inf() const {
    return min;
}

double interval::sup() const {
    return max;
}

bool interval::is_empty() const {
    return min > max;
}

double interval::size() const {
    return is_empty() ? 0.0 : max - min;
}

double interval::contains(double x) const {
    return min <= x && x <= max;
}

bool interval::surrounds(double x) const {
    return min < x && x < max;
}

double interval::clamp(double x) const {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);