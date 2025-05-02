#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
    int    image_height;   // Rendered image height
    double pixel_samples_scale;  // Color scale factor for a sum of pixel samples
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below

    color ray_color(const ray& r, int depth, const hittable& world) const;
    void initialize();
    vec3 sample_square() const;
    ray get_ray(int i, int j) const;
public:
    double aspect_ratio = 1.0;  // Ratio of image width over height
    int image_width  = 100;  // Rendered image width in pixel count
    int samples_per_pixel = 10;
    int max_depth = 10;
    void render(const hittable& world);
};

#endif