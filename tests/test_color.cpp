#include "color.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

TEST_CASE("write_color outputs correct RGB values") {
    std::ostringstream out;
    write_color(out, color(1.0, 0.0, 0.5));

    std::string result = out.str();
    REQUIRE(result == "255 0 127\n");
}
