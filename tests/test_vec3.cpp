#define CATCH_CONFIG_MAIN  // Only here!
#include <catch2/catch_all.hpp>
#include "vec3.h"
#include <cmath>

bool fp_eq(double a, double b) {
    double epsilon = 1e-9;
    return std::fabs(a-b) < epsilon;
}

TEST_CASE("floating point equality") {
    REQUIRE(fp_eq(2.467, 2.467) == true);
    REQUIRE(fp_eq(0, 0) == true);
    REQUIRE(fp_eq(190923, 190923) == true);
    REQUIRE(fp_eq(1, 0.9999999999999999) == true);
    REQUIRE(fp_eq(2.47, 2.5) == false);
    REQUIRE(fp_eq(0, 0.1) == false);
    REQUIRE(fp_eq(1.2, 2.3) == false);
}

TEST_CASE("vec3 default constructor") {
    vec3 v;
    REQUIRE(v.x() == 0);
    REQUIRE(v.y() == 0);
    REQUIRE(v.z() == 0);
}

TEST_CASE("vec3 value constructor") {
    vec3 v(2.5, 3.478, 7.89);
    REQUIRE(fp_eq(v.x(), 2.5));
    REQUIRE(fp_eq(v.y(), 3.478));
    REQUIRE(fp_eq(v.z(), 7.89));
};

TEST_CASE("vec3 - unary operator") {
    vec3 v(2.5, 3.478, 7.89);
    vec3 neg = -v;
    REQUIRE(fp_eq(neg.x(), -2.5));
    REQUIRE(fp_eq(neg.y(), -3.478));
    REQUIRE(fp_eq(neg.z(), -7.89));
}

TEST_CASE("vec3 [] operator") {
    const vec3 v(2.5, 3.478, 7.90);
    REQUIRE(fp_eq(v[0], 2.5));
    REQUIRE(fp_eq(v[1], 3.478));
    REQUIRE(fp_eq(v[2], 7.9));
}
