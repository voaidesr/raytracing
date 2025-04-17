#define CATCH_CONFIG_MAIN  // Only here!
#include <catch2/catch_all.hpp>
#include "vec3.h"

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
    vec3 v(2.5, 3.478, 7.90);
    REQUIRE(fp_eq(v[0], 2.5));
    REQUIRE(fp_eq(v[1], 3.478));
    REQUIRE(fp_eq(v[2], 7.9));
    v[1] += 2;
    REQUIRE(fp_eq(v[1], 5.478));
    REQUIRE_THROWS_AS(v[3], std::out_of_range);
    REQUIRE_THROWS_AS(v[-1], std::out_of_range);
}

TEST_CASE("vec3 equality operators") {
    vec3 x, y;
    REQUIRE(x == y);
    y[0] += 1;
    REQUIRE(x != y);

    vec3 a(1.5, 7.899, 8.29), b(1.5, 7.899, 8.29);
    REQUIRE(a == b);
}

TEST_CASE("vec3 += operator") {
    vec3 v, y(1, 2, 3);
    y += v;
    REQUIRE(y == vec3(1, 2, 3));
    v = vec3(1.3, 2.45, 7.8);
    y += v;
    REQUIRE(y == vec3(2.3, 4.45, 10.8));
}

TEST_CASE("vec3 -= operator") {
    vec3 v, y(1, 2, 3);
    y -= v;
    REQUIRE(y == vec3(1, 2, 3));
    v = vec3(1.3, 2.45, 7.8);
    v -= y;
    REQUIRE(v == vec3(0.3, 0.45, 4.8));
}

TEST_CASE("vec3 scalar multiplication operators") {
    vec3 v;
    v *= 1;
    REQUIRE(v == vec3(0, 0, 0));
    v = vec3(1, 2, 3);
    v *= 0;
    REQUIRE(v == vec3(0, 0, 0));
    v = vec3(1, 2, 3);
    v *= 2;
    REQUIRE(v == vec3(2, 4, 6));
    v *= 0.5;
    REQUIRE(v == vec3(1, 2, 3));
    v *= 2;
    REQUIRE(v == vec3(2, 4, 6));
    v /= 2;
    REQUIRE_THROWS_AS(v /= 0, std::invalid_argument);
}

TEST_CASE("vec3 length") {
    vec3 v;
    REQUIRE(v.length() == 0);
    v = vec3(1.0, 0, 0);
    REQUIRE(v.length() == 1);
    v = vec3(0, 1.0, 0);
    REQUIRE(v.length() == 1);
    v = vec3(0, 0, 1.0);
    REQUIRE(v.length() == 1);
    v = vec3(1, 2, 2);
    REQUIRE(fp_eq(v.length(), 3));
    v = vec3(1, 1, 0);
    REQUIRE(fp_eq(v.length(), std::sqrt(2)));
}

TEST_CASE("vec3 output operator prints correctly") {
    vec3 v(1.0, 2.5, -3.75);

    std::ostringstream out;
    out << v;
    REQUIRE(out.str() == "1 2.5 -3.75");
}

TEST_CASE("vec3 addition") {
    vec3 v, y(1, 2, 3);
    REQUIRE(v + y == vec3(1, 2, 3));
    REQUIRE(y + v == vec3(1, 2, 3));
    vec3 a(1.0, 2.0, 3.0);
    vec3 b(4.0, 5.0, 6.0);
    vec3 result = a + b;
    REQUIRE(result == vec3(5.0, 7.0, 9.0));
    a = vec3(-1.0, -2.0, -3.0);
    b = vec3(4.0, 5.0, 6.0);
    result = a + b;
    REQUIRE(result == vec3(3.0, 3.0, 3.0));
}

TEST_CASE("vec3 subtraction") {
    vec3 v, y(1, 2, 3);
    REQUIRE(v - y == vec3(-1, -2, -3));
    REQUIRE(y - v == vec3(1, 2, 3));

    vec3 a(4.0, 5.0, 6.0);
    vec3 b(1.0, 2.0, 3.0);
    vec3 result = a - b;
    REQUIRE(result == vec3(3.0, 3.0, 3.0));

    a = vec3(-1.0, -2.0, -3.0);
    b = vec3(4.0, 5.0, 6.0);
    result = a - b;
    REQUIRE(result == vec3(-5.0, -7.0, -9.0));
}

TEST_CASE("vec3 scalar multiplication") {
    vec3 v(1.0, -2.0, 3.5);

    REQUIRE(2.0 * v == vec3(2.0, -4.0, 7.0));
    REQUIRE(0.0 * v == vec3(0.0, 0.0, 0.0));
    REQUIRE(-1.0 * v == vec3(-1.0, 2.0, -3.5));
    REQUIRE(0.5 * v == vec3(0.5, -1.0, 1.75));

    REQUIRE(v * 2.0 == vec3(2.0, -4.0, 7.0));
    REQUIRE(v * 0.0== vec3(0.0, 0.0, 0.0));
    REQUIRE(v * -1.0 == vec3(-1.0, 2.0, -3.5));
    REQUIRE(v * 0.5 == vec3(0.5, -1.0, 1.75));
}

TEST_CASE("vec3 dot product") {
    vec3 v(1.0, 2.0, 3.0);
    vec3 u(4.0, -5.0, 6.0);

    REQUIRE(fp_eq(dot(v, u), 1*4 + 2*(-5) + 3*6));

    v = vec3(0.0, 0.0, 0.0);
    u = vec3(1.0, 2.0, 3.0);
    REQUIRE(fp_eq(dot(v, u), 0.0));

    v = vec3(1.0, 0.0, 0.0);
    u = vec3(0.0, 1.0, 0.0);
    REQUIRE(fp_eq(dot(v, u), 0.0));

    v = vec3(2.0, 2.0, 2.0);
    u = vec3(2.0, 2.0, 2.0);
    REQUIRE(fp_eq(dot(v, u), 12.0));

    v = vec3(1.0, 2.0, 3.0);
    u = vec3(-1.0, -2.0, -3.0);
    REQUIRE(fp_eq(dot(v, u), -14.0));
}

TEST_CASE("vec3 cross product") {
    vec3 u(1.0, 0.0, 0.0);
    vec3 v(0.0, 1.0, 0.0);
    vec3 result = cross(u, v);
    REQUIRE(result == vec3(0.0, 0.0, 1.0));  // right-hand rule

    u = vec3(0.0, 1.0, 0.0);
    v = vec3(0.0, 0.0, 1.0);
    result = cross(u, v);
    REQUIRE(result == vec3(1.0, 0.0, 0.0));

    u = vec3(0.0, 0.0, 1.0);
    v = vec3(1.0, 0.0, 0.0);
    result = cross(u, v);
    REQUIRE(result == vec3(0.0, 1.0, 0.0));

    // parallel vectors, zero vector
    u = vec3(1.0, 2.0, 3.0);
    v = vec3(2.0, 4.0, 6.0); // v = 2 * u
    result = cross(u, v);
    REQUIRE(result == vec3(0.0, 0.0, 0.0));

    // opposite direction (still parallel)
    u = vec3(1.0, 2.0, 3.0);
    v = vec3(-1.0, -2.0, -3.0);
    result = cross(u, v);
    REQUIRE(result == vec3(0.0, 0.0, 0.0));
}

TEST_CASE("vec3 unit_vector") {
    vec3 v(3.0, 0.0, 0.0);
    vec3 u = unit_vector(v);
    REQUIRE(u == vec3(1.0, 0.0, 0.0));
    REQUIRE(fp_eq(u.length(), 1.0));

    v = vec3(0.0, -4.0, 0.0);
    u = unit_vector(v);
    REQUIRE(u == vec3(0.0, -1.0, 0.0));
    REQUIRE(fp_eq(u.length(), 1.0));

    v = vec3(1.0, 2.0, 2.0);
    u = unit_vector(v);
    REQUIRE(fp_eq(u.length(), 1.0));

    v = vec3(0.0, 0.0, 1.0);
    u = unit_vector(v);
    REQUIRE(u == vec3(0.0, 0.0, 1.0));
    REQUIRE(fp_eq(u.length(), 1.0));
}