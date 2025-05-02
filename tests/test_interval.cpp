#include "utils.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Default constructor creates an empty interval")
{
    interval i;
    REQUIRE(i.size() == 0);
    REQUIRE(i.contains(0.0) == false);
}

TEST_CASE("Parameterized constructor creates a valid interval")
{
    interval i(0.0, 10.0);
    REQUIRE(i.size() == 10.0);
    REQUIRE(i.contains(5.0) == true);
    REQUIRE(i.contains(0.0) == true);
    REQUIRE(i.contains(10.0) == true);
    REQUIRE(i.contains(15.0) == false);
}

TEST_CASE("inf and sup work correctly")
{
    interval i(0.0, 10.0);
    REQUIRE(fp_eq(i.inf(), 0.0));
    REQUIRE(fp_eq(i.sup(), 10.0));
    REQUIRE(interval::empty.inf() == infinity);
    REQUIRE(interval::empty.sup() == -infinity);
    REQUIRE(interval::universe.inf() == -infinity);
    REQUIRE(interval::universe.sup() == infinity);
}

TEST_CASE("is_empty works correctly")
{
    interval empty_interval = interval::empty;
    interval non_empty_interval(0.0, 10.0);

    REQUIRE(empty_interval.is_empty() == true);
    REQUIRE(non_empty_interval.is_empty() == false);
}

TEST_CASE("Surround method works correctly")
{
    interval i(0.0, 10.0);
    REQUIRE(i.surrounds(5.0) == true);
    REQUIRE(i.surrounds(0.0) == false);
    REQUIRE(i.surrounds(10.0) == false);
    REQUIRE(i.surrounds(15.0) == false);
}

TEST_CASE("Static constants empty and universe")
{
    REQUIRE(interval::empty.size() == 0);
    REQUIRE(interval::empty.contains(0.0) == false);    // no value is inside empty
    REQUIRE(interval::universe.contains(0.0) == true);  // any value is inside the universe
}

TEST_CASE("Interval containing negative and positive values")
{
    interval i(-5.0, 5.0);
    REQUIRE(i.size() == 10.0);         // size of the interval should be 10
    REQUIRE(i.contains(-3.0) == true); // -3 is inside
    REQUIRE(i.contains(0.0) == true);  // 0 is inside
    REQUIRE(i.contains(3.0) == true);  // 3 is inside
    REQUIRE(i.contains(6.0) == false); // 6 is outside
}
