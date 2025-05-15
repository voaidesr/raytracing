#include "sphere.h"

sphere::sphere(const point3& center, double radius, shared_ptr<material> mat) : center(center), radius(std::fmax(0,radius)), mat(mat) {}

bool sphere::hit(const ray& r, interval ray_t, hit_record& rec) const {
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = h*h - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = std::sqrt(discriminant);

    double t0 = (h - sqrtd) / a;
    double t1 = (h + sqrtd) / a;

    if (t0 > t1) std::swap(t0, t1);

    if (!ray_t.surrounds(t0)) {
        t0 = t1;
        if (!ray_t.surrounds(t0))
            return false;
    }

    rec.t       = t0;
    rec.t_exit  = t1;
    rec.p       = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat     = mat;
    return true;
}
