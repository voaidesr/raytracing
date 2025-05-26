#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <cmath>

#include "material.h"
#include "ray.h"
#include "interval.h"
#include "vec3.h"

static constexpr double EPS = 1e-6;

TEST_CASE("Schlick Fresnel approximation at cosθ = 1 returns F0", "[material]") {
    color F0{0.2, 0.4, 0.6};
    auto res = schlick_fresnel(F0, 1.0);
    REQUIRE(res == F0);
}

TEST_CASE("Schlick Fresnel approximation at cosθ = 0 returns white", "[material]") {
    color F0{0.2, 0.4, 0.6};
    auto res = schlick_fresnel(F0, 0.0);
    REQUIRE(res == color(1, 1, 1));
}

TEST_CASE("Lambertian scatter always returns true and correct attenuation and origin", "[material]") {
    color albedo{0.3, 0.5, 0.7};
    lambertian mat(albedo);

    ray r_in(point3(0, 0, 0), vec3(1, 0, 0));
    hit_record rec;
    rec.p = point3(1, 2, 3);
    rec.normal = vec3(0, 1, 0);
    rec.front_face = true;

    color attenuation;
    ray scattered{point3(), vec3()};

    bool did_scatter = mat.scatter(r_in, rec, attenuation, scattered);
    REQUIRE(did_scatter);
    REQUIRE(attenuation == albedo);
    REQUIRE(scattered.origin() == rec.p);
    REQUIRE(scattered.direction().length_squared() > EPS);
}

TEST_CASE("Metal scatter with zero fuzz equals perfect reflection and schlick attenuation", "[material]") {
    color albedo{0.8, 0.6, 0.2};
    metal mat(albedo, 0.0);

    vec3 in_dir = unit_vector(vec3(0, -1, 0));
    ray  r_in(point3(0, 0, 0), in_dir);

    hit_record rec;
    rec.p = point3(0, 0, 0);
    rec.normal = vec3(0, 1, 0);
    rec.front_face = true;
    rec.t = 1.0;
    rec.t_exit = 2.0;

    color attenuation;
    ray scattered{point3(), vec3()};

    bool did_scatter = mat.scatter(r_in, rec, attenuation, scattered);
    REQUIRE(did_scatter);
    REQUIRE(scattered.origin() == rec.p);

    vec3 expected_dir = reflect(in_dir, rec.normal);
    expected_dir = unit_vector(expected_dir);
    REQUIRE(scattered.direction() == expected_dir);

    double cosθ = std::fmax(dot(-in_dir, rec.normal), 0.0);
    color expected_atten = schlick_fresnel(albedo, cosθ);
    REQUIRE(attenuation == expected_atten);
}

TEST_CASE("Dielectric reflectance matches Schlick formula", "[material]") {
    double ri = 1.5;
    double cosθ = 0.5;
    double ref = dielectric::reflectance(cosθ, ri);

    double r0 = (1 - ri) / (1 + ri);
    r0 = r0 * r0;
    double expected = r0 + (1 - r0) * std::pow((1 - cosθ), 5);

    REQUIRE(std::abs(ref - expected) < EPS);
}
