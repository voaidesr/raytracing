#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "property.h"

class camera {
    int    image_height;
    double pixel_samples_scale;
    point3 center;
    point3 pixel00_loc;
    vec3   pixel_delta_u;
    vec3   pixel_delta_v;
    vec3   u, v, w;
    vec3   defocus_disk_u;
    vec3   defocus_disk_v;

    color ray_color(const ray& r, int depth, const hittable& world) const;
    void initialize();
    vec3 sample_square() const;
    point3 defocus_disk_sample() const;
    ray get_ray(int i, int j) const;

    camera()  = default;
    ~camera() = default;
    camera(const camera&)            = delete;
    camera(camera&&)                 = delete;
    camera& operator=(const camera&) = delete;
    camera& operator=(camera&&)      = delete;

public:
    Property<double> aspect_ratio = Property<double>(1.0);
    Property<int> image_width = Property<int>(100);
    Property<int> samples_per_pixel = Property<int>(10);
    Property<int> max_depth = Property<int>(10);
    Property<double> vfov = Property<double>(90);
    Property<point3> lookfrom = Property<point3>(point3(0,0,0));
    Property<point3> lookat = Property<point3>(point3(0,0,-1));
    Property<vec3> vup = Property<vec3>(vec3(0,1,0));
    Property<double> defocus_angle = Property<double>(0);
    Property<double> focus_dist = Property<double>(10);

    static camera& instance();
    void render(const hittable& world);
};

#endif
