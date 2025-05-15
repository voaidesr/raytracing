#include "camera.h"
#include "material.h"
#include <omp.h>
#include <atomic>
#include <sstream>
#include "display.h"

    double& camera::aspect_ratio() { return _aspect_ratio; }
    int& camera::image_width() { return _image_width; }
    int& camera::samples_per_pixel() { return _samples_per_pixel; }
    int& camera::max_depth() { return _max_depth; }
    double& camera::vfov() { return _vfov; }
    point3& camera::lookfrom() { return _lookfrom; }
    point3& camera::lookat() { return _lookat; }
    vec3& camera::vup() { return _vup; }
    double& camera::defocus_angle() { return _defocus_angle; }
    double& camera::focus_dist() { return _focus_dist; }

    color camera::ray_color(const ray& r0, int depth, const hittable& world) const {
        ray    r      = r0;
        color  col    = color(1,1,1);
        for (int i = 0; i < depth; ++i) {
            hit_record rec;
            if (!world.hit(r, interval(0.001, infinity), rec)) {
                // sky
                auto unit_d = unit_vector(r.direction());
                auto t      = 0.5*(unit_d.y()+1.0);
                col = col * ((1.0-t)*color(1,1,1) + t*color(0.5,0.7,1.0));
                break;
            }
            ray    scattered;
            color  attenuation;
            if (!rec.mat->scatter(r, rec, attenuation, scattered)) {
                col = color(0,0,0);
                break;
            }
            col = col * attenuation;
            r   = scattered;
        }
        return col;
}

void camera::initialize() {
    image_height = int(_image_width / _aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / _samples_per_pixel;

    center = _lookfrom;

    auto theta = degrees_to_radians(_vfov);
    auto h = std::tan(theta / 2);
    auto viewport_height = 2 * h * _focus_dist;
    auto viewport_width = viewport_height * (double(_image_width) / image_height);

    w = unit_vector(_lookfrom - _lookat);
    u = unit_vector(cross(_vup, w));
    v = cross(w, u);

    vec3 viewport_u = viewport_width * u;
    vec3 viewport_v = viewport_height * -v;

    pixel_delta_u = viewport_u / _image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = center - (_focus_dist * w) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    auto defocus_radius = _focus_dist * std::tan(degrees_to_radians(_defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

ray camera::get_ray(int i, int j) const {
    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
                      + ((i + offset.x()) * pixel_delta_u)
                      + ((j + offset.y()) * pixel_delta_v);

    auto ray_origin = (_defocus_angle <= 0) ? center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
}

vec3 camera::sample_square() const {
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

point3 camera::defocus_disk_sample() const {
    // Returns a random point in the camera defocus disk.
    auto p = random_in_unit_disk();
    return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}

void camera::render(const hittable& world) {
    initialize();
    Display display(_image_width, image_height);

    std::vector<color> framebuffer(_image_width * image_height);

    for (int j = 0; j < image_height && display.is_open(); ++j) {
        #pragma omp parallel for schedule(static)
            for (int i = 0; i < _image_width; ++i) {
                color pixel(0,0,0);
                for (int s = 0; s < _samples_per_pixel; ++s)
                    pixel += ray_color(get_ray(i,j), _max_depth, world);
                pixel *= pixel_samples_scale;
                color gam = linear_to_gamma(pixel);
                framebuffer[j*_image_width + i] = pixel;       // if you still need it
                display.set_pixel(i, j, gam);
            }
        display.update();
        std::clog << "\rScanlines remaining: "
                  << (image_height - 1 - j) << ' ' << std::flush;
    }

    std::cout << "P3\n" << _image_width << ' ' << image_height << "\n255\n";
    for (const auto& px : framebuffer) write_color(std::cout, px);

    std::clog << "\rDone.                 \n";
}