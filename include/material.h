#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
        return false;
    }
};

class lambertian : public material {
    color albedo;
public:
    lambertian(const color& albedo);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
};

class metal : public material {
    color albedo;
    double fuzz;
public:
    metal(const color& albedo, double fuzz);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
};

class dielectric : public material {
    public:
      dielectric(double refraction_index);

      bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

      static double reflectance(double cosine, double refraction_index);

    private:
        double refraction_index;
};


#endif