#include "camera.h"
#include "material.h"
#include "display.h"
#include "property.h"
#include <omp.h>
#include <vector>
#include <iostream>
#include <sstream>

camera& camera::instance() {
    static camera cam;
    return cam;
}

color camera::ray_color(const ray& r0, int depth, const hittable& world) const {
    ray r = r0;
    color col = color(1,1,1);

    for (int bounce = 0; bounce < depth; ++bounce) {
        hit_record rec;
        if (!world.hit(r, interval(0.001, infinity), rec)) {
            vec3 unit_d = unit_vector(r.direction());
            auto t = 0.5 * (unit_d.y() + 1.0);
            col = col * ((1.0 - t) * color(1,1,1) + t * color(0.5,0.7,1.0));
            break;
        }

        ray scattered;
        color attenuation;
        if (!rec.mat->scatter(r, rec, attenuation, scattered)) {
            col = color(0,0,0);
            break;
        }

        col = col * attenuation;
        r = scattered;
    }
    return col;
}

vec3 camera::sample_square() const {
    return vec3(random_double() - 0.5,
                random_double() - 0.5,
                0.0);
}

point3 camera::defocus_disk_sample() const {
    vec3 p = random_in_unit_disk();
    return center + p[0] * defocus_disk_u + p[1] * defocus_disk_v;
}

void camera::initialize() {
    try {
        clamp(image_width, 10, 3000);
        clamp(samples_per_pixel, 1, 1000);
        clamp(vfov, 1.0, 180.0);
        clamp(focus_dist, 0.01, 10000.0);
        clamp(defocus_angle, 0.0, 45.0);

        if (aspect_ratio <= 0.0) {
            throw std::invalid_argument("aspect_ratio must be positive");
        }

        image_height = static_cast<int>(image_width / aspect_ratio);
        if (image_height < 1) image_height = 1;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = lookfrom;

        const double theta = degrees_to_radians(vfov);
        if (theta <= 0.0 || theta >= M_PI) {
            throw std::invalid_argument("vfov must be between 0 and 180 degrees exclusive");
        }
        const double h = std::tan(theta * 0.5);
        const double viewport_height = 2.0 * h * focus_dist;
        const double viewport_width  = viewport_height * (static_cast<double>(image_width) / image_height);

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        const vec3 viewport_u = viewport_width * u;
        const vec3 viewport_v = viewport_height * (-v);

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        const vec3 viewport_upper_left = center
                                         - focus_dist * w
                                         - viewport_u * 0.5
                                         - viewport_v * 0.5;

        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        const double defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle * 0.5));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    } catch (const std::exception& e) {
        throw;
    }
}

ray camera::get_ray(int i, int j) const {
    const vec3 offset = sample_square();

    const point3 pixel_sample = pixel00_loc
                              + (i + offset.x()) * pixel_delta_u
                              + (j + offset.y()) * pixel_delta_v;

    const point3 origin = (defocus_angle == 0) ? center : defocus_disk_sample();
    const vec3 direction = pixel_sample - origin;

    return ray(origin, direction);
}

void camera::render(const hittable& world) {
    try {
        initialize();
    } catch (const std::exception& e) {
        throw;
    }

    Display display(image_width, image_height);
    std::vector<color> framebuffer(image_width * image_height);

    for (int j = 0; j < image_height && display.is_open(); ++j) {
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < image_width; ++i) {
            color px(0,0,0);
            for (int s = 0; s < samples_per_pixel; ++s)
                px += ray_color(get_ray(i, j), max_depth, world);
            px *= pixel_samples_scale;
            framebuffer[j * image_width + i] = px;
            auto gamma_px = linear_to_gamma(px);
            display.set_pixel(i, j, gamma_px);
        }
        display.update();
        std::clog << "\rScanlines remaining: " << (image_height - 1 - j) << ' ' << std::flush;
    }

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (const auto& px : framebuffer)
        write_color(std::cout, px);

    std::clog << "\rDone.                    \n";
}