#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "hittable.h"
#include "ray.h"

class sphere : public hittable {
private:
    point3 center;
    double radius;
public:
    sphere(const point3& center, double radius);

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override;
};

#endif