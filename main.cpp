#include "utils.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "camera.h"
#include "scene.h"

int main() {
    Scene5 scene;
    auto world = scene.create();
    // world->clear();

    auto& cam = camera::instance();

    cam.aspect_ratio.set(16.0 / 9.0);
    // cam.aspect_ratio.set(-1);
    cam.image_width.set(1000);
    cam.samples_per_pixel.set(50);
    cam.max_depth.set(20);

    cam.vfov.set(45);
    cam.lookfrom.set(point3(0,0.5,1));
    cam.lookat.set(point3(0,0,-1));
    cam.vup.set(vec3(0,1,0));
    cam.defocus_angle.set(0.2);
    cam.focus_dist.set(2);

    try {
        cam.render(*world);
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mEncountered issue: " << e.what() << "\033[0m" << std::endl;
    }
}
