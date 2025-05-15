#ifndef HITTABLE_H
#define HITTABLE_H

#include "utils.h"

class material;

// this could be a struct
class hit_record {
public:
    point3 p;
    vec3 normal;
    shared_ptr<material> mat;
    double t;
    double t_exit;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        vec3 unit_outward_normal = unit_vector(outward_normal);
        front_face = dot(r.direction(), unit_outward_normal) < 0;
        normal = front_face ? unit_outward_normal : -unit_outward_normal;
    }
};

class hittable {
public:
    virtual ~hittable() = default;

    // pure virtual function, cannot be instantiated on its own
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};
#endif