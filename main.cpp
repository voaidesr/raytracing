#include "utils.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "camera.h"

int main() {
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.50, color(1,1,1), color(0.5, 1, 0.7));
    auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0);

    world.add(make_shared<sphere>(point3( 0.0, -1000.5, -1.0), 1000.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    auto& cam = camera::instance();

    cam.aspect_ratio.set(16.0 / 9.0);
    cam.image_width.set(1500);
    cam.samples_per_pixel.set(20);
    cam.max_depth.set(50);

    cam.vfov.set(45);
    cam.lookfrom.set(point3(-2,0,1));
    cam.lookat.set(point3(0,0,-1));
    cam.vup.set(vec3(0,1,0));
    cam.defocus_angle.set(2);
    cam.focus_dist.set(2);

    cam.render(world);
}
