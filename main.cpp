#include "utils.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "camera.h"

int main() {
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.314, 0.216, 0.082));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right  = make_shared<metal>(color(0.827, 0.686, 0.216));

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    // world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    // world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    // world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    world.add(make_shared<sphere>(point3(-0.7, 0.0, -0.5), 0.5, material_left));
    world.add(make_shared<sphere>(point3(0.7, 0.0, -0.5), 0.5, material_left));

    camera cam;

    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 1500;
    cam.samples_per_pixel = 50;
    cam.max_depth = 3;
    cam.render(world);
}