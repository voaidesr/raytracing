#include "utils.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "camera.h"
#include "scene.h"

int main() {
    Scene scene;
    auto world = scene.create();

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

    cam.render(*world);
}
