#include "sphere.h"
#include "ray.h"
#include <catch2/catch_test_macros.hpp>
#include <cmath>

TEST_CASE("ray intersects sphere at two points") {
    point3 center(0.0, 0.0, -5.0);
    double radius = 1.0;
    sphere s(center, radius);

    point3 origin(0.0, 0.0, 0.0);
    vec3 direction(0.0, 0.0, -1.0);

    ray r(origin, direction);
    hit_record rec;

    REQUIRE(s.hit(r, 0.001, 1000.0, rec) == true);
    REQUIRE(rec.t > 0.0);
    REQUIRE(rec.normal == vec3(0.0, 0.0, 1.0));
}
