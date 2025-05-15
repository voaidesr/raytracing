#include "material.h"

// Schlick’s approximation for metal
inline color schlick_fresnel(const color &F0, double cosθ) {
    double inv = 1.0 - cosθ;
    double pow5 = inv*inv*inv*inv*inv;
    return F0 + (color(1,1,1) - F0) * pow5;
}

lambertian::lambertian(const color& albedo) : albedo(albedo) {}

bool lambertian::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
    auto scatter_direction = rec.normal + random_unit_vector();

    if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

metal::metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

bool metal::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    vec3 unit_in = unit_vector(r_in.direction());
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered = ray(rec.p, reflected);
    if (dot(scattered.direction(), rec.normal) <= 0)
        return false;
    double cosθ = fmax(dot(-unit_in, rec.normal), 0.0);
    attenuation = schlick_fresnel(albedo, cosθ);

    return true;
}

dielectric::dielectric(double refraction_index, color albedo ) : refraction_index(refraction_index), albedo(albedo) {}

bool dielectric::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
    attenuation = this->get_color();
    color sigma_a = color(0, 1, 1);
    double ri = rec.front_face ? (1.0/refraction_index) : refraction_index;

    vec3 unit_direction = unit_vector(r_in.direction());
    double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    vec3 direction;


    if (cannot_refract || reflectance(cos_theta, ri) > random_double())
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, ri);
    double d = (rec.t_exit - rec.t) * r_in.direction().length();
    color absorb{-sigma_a.x()*d, -sigma_a.y()*d, -sigma_a.z()*d};
    color T{expf(absorb.x()), expf(absorb.y()), expf(absorb.z())};
    attenuation = albedo * T;
    scattered  = ray(r_in.at(rec.t), direction);
    return true;
}

double dielectric::reflectance(double cosine, double refraction_index) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0*r0;
    return r0 + (1-r0)*std::pow((1 - cosine),5);
}