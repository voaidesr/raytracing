#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
        return false;
    }

    virtual color get_color() const {
        return color(1.0f, 1.0f, 1.0f);
    }
};

class lambertian : public material {
    color albedo;
public:
    lambertian(const color& albedo);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

    color get_color() const override {
        return albedo;
    }
};

class metal : public material {
    color albedo;
    double fuzz;
public:
    metal(const color& albedo);
    metal(const color& albedo, double fuzz);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

    color get_color() const override {
        return albedo;
    }
};

class dielectric : public material {
    color albedo = color(1,1,1);
    color sigma_a  = color(0.1, 0.1, 0.1);
    double refraction_index;
public:
    dielectric(double refraction_index);
    dielectric(double refraction_index, const color& albedo);
    dielectric(double refraction_index, const color& albedo, const color& sigma_a);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

    static double reflectance(double cosine, double refraction_index);

    color get_color() const override {
        return albedo;
    }
};


#endif