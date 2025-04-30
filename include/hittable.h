#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record {
public:
    point3 p;
    vec3 normal;
    double t;
};

class hittable {
public:
    virtual ~hittable() = default;

    // pure virtual function, cannot be instantiated on its own
    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};
#endif