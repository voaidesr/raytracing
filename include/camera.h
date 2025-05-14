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
    vec3   u, v, w;              // Camera frame basis vectors

    color ray_color(const ray& r, int depth, const hittable& world) const;
    void initialize();
    vec3 sample_square() const;
    ray get_ray(int i, int j) const;

    // accessible through methods that return reference
    double _aspect_ratio = 1.0;  // Ratio of image width over height
    int _image_width  = 100;  // Rendered image width in pixel count
    int _samples_per_pixel = 10;
    int _max_depth = 10;
    double _vfov = 90;  // Vertical view angle (field of view)
    point3 _lookfrom = point3(0,0,0);   // Point camera is looking from
    point3 _lookat   = point3(0,0,-1);  // Point camera is looking at
    vec3   _vup      = vec3(0,1,0);     // Camera-relative "up" direction
public:
    double& aspect_ratio();
    int& image_width();
    int& samples_per_pixel();
    int& max_depth();
    double& vfov();
    point3& lookfrom();
    point3& lookat();
    vec3& vup();
    void render(const hittable& world);
};

#endif