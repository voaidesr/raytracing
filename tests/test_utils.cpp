#include "utils.h"
#include <catch2/catch_test_macros.hpp>

extern bool fp_eq(double a, double b); // if defined elsewhere

TEST_CASE("degrees_to_radians computes correct values") {
    REQUIRE(fp_eq(degrees_to_radians(0.0), 0.0));
    REQUIRE(fp_eq(degrees_to_radians(180.0), pi));
    REQUIRE(fp_eq(degrees_to_radians(90.0), pi / 2.0));
    REQUIRE(fp_eq(degrees_to_radians(360.0), 2.0 * pi));
}
