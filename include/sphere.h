#ifndef SPHERE_H
#define SPHERE_H

#include <utils.h>
#include "hittable.h"

class sphere : public hittable {
private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
public:
    sphere(const point3& center, double radius, shared_ptr<material> mat);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};

#endif