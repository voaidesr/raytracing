// #include "hittable_list.h"
// #include "sphere.h"
// #include "ray.h"
// #include "vec3.h"  // assuming this is where point3/vec3 and fp_eq are defined
// #include <catch2/catch_test_macros.hpp>
// #include <memory>

// extern bool fp_eq(double a, double b);  // if fp_eq is not in a header

// TEST_CASE("ray hits one sphere in hittable_list") {
//     auto sphere_ptr = std::make_shared<sphere>(point3(0, 0, -5), 1.0);
//     hittable_list world;
//     world.add(sphere_ptr);

//     ray r(point3(0, 0, 0), vec3(0, 0, -1));
//     hit_record rec;

//     REQUIRE(world.hit(r, interval(0.001, 1000.0), rec) == true);
//     REQUIRE(rec.t > 0.0);
//     REQUIRE(fp_eq(rec.p.x(), 0.0));
//     REQUIRE(fp_eq(rec.p.y(), 0.0));
//     REQUIRE(fp_eq(rec.p.z(), -4.0));  // hit point: z = -4
// }

// TEST_CASE("ray misses all objects in hittable_list") {
//     auto sphere_ptr = std::make_shared<sphere>(point3(0, 0, -5), 1.0);
//     hittable_list world;
//     world.add(sphere_ptr);

//     ray r(point3(0, 0, 0), vec3(0, 1, 0));  // ray goes upward
//     hit_record rec;

//     REQUIRE(world.hit(r, interval(0.001, 1000.0), rec) == false);
// }

// TEST_CASE("ray hits closest of two spheres in hittable_list") {
//     auto near_sphere = std::make_shared<sphere>(point3(0, 0, -3), 0.5);
//     auto far_sphere  = std::make_shared<sphere>(point3(0, 0, -10), 2.0);
//     hittable_list world;
//     world.add(near_sphere);
//     world.add(far_sphere);

//     ray r(point3(0, 0, 0), vec3(0, 0, -1));
//     hit_record rec;

//     REQUIRE(world.hit(r, interval(0.001, 1000.0), rec) == true);
//     REQUIRE(fp_eq(rec.p.z(), -2.5));  // closest hit point (sphere at -3, radius 0.5)
// }
