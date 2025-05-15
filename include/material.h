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
    metal(const color& albedo, double fuzz);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

    color get_color() const override {
        return albedo;
    }
};

class dielectric : public material {
    color albedo;
    double refraction_index;
public:
    dielectric(double refraction_index, color albedo);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

    static double reflectance(double cosine, double refraction_index);

    color get_color() const override {
        return albedo;
    }
};


#endif