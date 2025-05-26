#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <cmath>

#include "sphere.h"
#include "ray.h"
#include "material.h"

static constexpr double EPS = 1e-6;

TEST_CASE("Ray misses the sphere", "[sphere]") {
    auto mat = std::make_shared<lambertian>(color(1,1,1));
    sphere s(point3(0,0,-5), 1.0, mat);

    ray r(point3(0,2,0), vec3(1,0,0));
    hit_record rec;

    REQUIRE_FALSE(s.hit(r, interval(0.001, 1000.0), rec));
}

TEST_CASE("Ray intersects sphere at two points", "[sphere]") {
    auto mat = std::make_shared<lambertian>(color(1,0,0));
    sphere s(point3(0,0,-5), 1.0, mat);

    ray r(point3(0,0,0), vec3(0,0,-1));
    hit_record rec;

    REQUIRE(s.hit(r, interval(0.001, 1000.0), rec));

    REQUIRE(rec.t > 3.0);
    REQUIRE(rec.t < 5.0);

    REQUIRE(rec.t_exit > rec.t);
    REQUIRE(rec.normal == vec3(0,0,1));
}

