#include "ray.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("ray construction and evaluation") {
    point3 origin(1.0, 2.0, 3.0);
    vec3 direction(4.0, 5.0, 6.0);

    ray r(origin, direction);

    REQUIRE(r.origin() == origin);
    REQUIRE(r.direction() == direction);

    REQUIRE(r.at(0.0) == origin);

    REQUIRE(r.at(1.0) == origin + direction);

    REQUIRE(r.at(2.0) == origin + 2.0 * direction);
}
