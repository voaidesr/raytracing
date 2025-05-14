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

color camera::ray_color(const ray& r, int depth, const hittable& world) const {
    if (depth <= 0)
        return color(0, 0, 0);

    hit_record rec;

    if (world.hit(r, interval(0.001, infinity), rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, depth - 1, world);
        return color(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

void camera::initialize() {
    image_height = int(_image_width / _aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / _samples_per_pixel;

    center = _lookfrom;

    auto focal_length = (_lookfrom - _lookat).length();
    auto theta = degrees_to_radians(_vfov);
    auto h = std::tan(theta / 2);
    auto viewport_height = 2 * h * focal_length;
    auto viewport_width = viewport_height * (double(_image_width) / image_height);

    w = unit_vector(_lookfrom - _lookat);
    u = unit_vector(cross(_vup, w));
    v = cross(w, u);

    vec3 viewport_u = viewport_width * u;
    vec3 viewport_v = viewport_height * -v;

    pixel_delta_u = viewport_u / _image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = center - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

ray camera::get_ray(int i, int j) const {
    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
                      + ((i + offset.x()) * pixel_delta_u)
                      + ((j + offset.y()) * pixel_delta_v);

    auto ray_origin = center;
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
}

vec3 camera::sample_square() const {
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

void camera::render(const hittable& world) {
    initialize();
    Display display(_image_width, image_height);

    std::vector<color> framebuffer(_image_width * image_height);

    for (int j = 0; j < image_height && display.is_open(); ++j) {
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < _image_width; ++i) {
            color pixel(0, 0, 0);
            for (int s = 0; s < _samples_per_pixel; ++s)
                pixel += ray_color(get_ray(i, j), _max_depth, world);

            pixel *= pixel_samples_scale;
            framebuffer[j * _image_width + i] = pixel;
        }

        for (int i = 0; i < _image_width; ++i) {
            const color& lin = framebuffer[j * _image_width + i];
            color gam = linear_to_gamma(lin);
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