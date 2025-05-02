#ifndef SPHERE_H
#define SPHERE_H

#include <utils.h>
#include "hittable.h"

class sphere : public hittable {
private:
    point3 center;
    double radius;
public:
    sphere(const point3& center, double radius);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};

#endif