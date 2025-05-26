#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <cmath>
#include "hittable_list.h"
#include "sphere.h"
#include "ray.h"
#include "interval.h"
#include "material.h"

static constexpr double EPS = 1e-6;

TEST_CASE("Empty hittable_list yields no hit", "[hittable_list]") {
    hittable_list world;
    ray r(point3(0,0,0), vec3(1,0,0));
    hit_record rec;

    REQUIRE_FALSE(world.hit(r, interval(0.001, 1000.0), rec));
}

TEST_CASE("hittable_list with one sphere that misses", "[hittable_list]") {
    auto mat = std::make_shared<lambertian>(color(1,1,1));
    auto sph = std::make_shared<sphere>(point3(0,5,-5), 1.0, mat);
    hittable_list world;
    world.add(sph);

    ray r(point3(0,0,0), vec3(1,0,0));
    hit_record rec;

    REQUIRE_FALSE(world.hit(r, interval(0.001, 1000.0), rec));
}

TEST_CASE("hittable_list with one sphere that hits", "[hittable_list]") {
    auto mat = std::make_shared<lambertian>(color(0.5,0.5,0.5));
    auto sph = std::make_shared<sphere>(point3(0,0,-5), 2.0, mat);
    hittable_list world;
    world.add(sph);

    ray r(point3(0,0,0), vec3(0,0,-1));
    hit_record rec;

    REQUIRE(world.hit(r, interval(0.001, 1000.0), rec));
    REQUIRE(rec.t > 2.0 - EPS);
    REQUIRE(rec.t < 3.0 + EPS);
    REQUIRE(rec.normal == vec3(0,0,1));
}

TEST_CASE("hittable_list selects closest hit among multiple objects", "[hittable_list]") {
    auto mat = std::make_shared<lambertian>(color(1,0,0));
    auto near_sph = std::make_shared<sphere>(point3(0,0,-3), 0.5, mat);
    auto far_sph  = std::make_shared<sphere>(point3(0,0,-5), 1.0, mat);
    hittable_list world;
    world.add(far_sph);
    world.add(near_sph);

    ray r(point3(0,0,0), vec3(0,0,-1));
    hit_record rec;

    REQUIRE(world.hit(r, interval(0.001, 1000.0), rec));
    REQUIRE(std::abs(rec.t - 2.5) < EPS);
    REQUIRE(rec.normal == vec3(0,0,1));
}

TEST_CASE("clear() removes all objects", "[hittable_list]") {
    auto mat = std::make_shared<lambertian>(color(0.2,0.3,0.4));
    auto sph = std::make_shared<sphere>(point3(0,0,-2), 1.0, mat);
    hittable_list world;
    world.add(sph);
    world.clear();

    ray r(point3(0,0,0), vec3(0,0,-1));
    hit_record rec;

    REQUIRE_FALSE(world.hit(r, interval(0.001, 1000.0), rec));
}
