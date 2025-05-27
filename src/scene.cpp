#include "scene.h"

std::shared_ptr<hittable_list> Scene::create() const {
    auto world = std::make_shared<hittable_list>();

    auto m_ground = make_shared<lambertian>(color(0.52, 0.37, 0.26));
    auto m_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto m_left   = make_shared<dielectric>(1.50, color(1,1,1), color(0.5, 1, 0.7));
    auto m_bubble = make_shared<dielectric>(1.00 / 1.50);
    auto m_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world->add(make_shared<sphere>(point3( 0.0, -1000.5, -1.0), 1000.0, m_ground));
    world->add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5,   m_center));
    world->add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5,   m_left));
    world->add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.4,   m_bubble));
    world->add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5,   m_right));

    return world;
}

std::shared_ptr<hittable_list> Scene2::create() const {
    auto world = std::make_shared<hittable_list>();

    auto m_ground = std::make_shared<lambertian>(color(0.52, 0.37, 0.26));
    auto m_mirror = std::make_shared<metal>(color(0.9, 0.9, 0.9), 0.0);
    auto m_glass1 = std::make_shared<dielectric>(1.5);
    auto m_glass2 = std::make_shared<dielectric>(1.5);

    world->add(std::make_shared<sphere>(point3(0.0, -1000.5, -1.0), 1000.0, m_ground));
    world->add(std::make_shared<sphere>(point3(-1.5, 0.0, -1.0), 1.0, m_mirror));
    world->add(std::make_shared<sphere>(point3(1.5, 0.0, -1.0), 1.0, m_mirror));
    world->add(std::make_shared<sphere>(point3(-0.5, 0.5, -1.0), 0.5, m_glass1));
    world->add(std::make_shared<sphere>(point3(0.5, 0.5, -1.0), 0.5, m_glass2));

    return world;
}

std::shared_ptr<hittable_list> Scene3::create() const {
    auto world = std::make_shared<hittable_list>();

    auto m_ground = std::make_shared<lambertian>(color(0.52, 0.37, 0.26));
    auto m_mirror = std::make_shared<metal>(color(0.9, 0.9, 0.9), 0.0);
    auto m_mirror2 = std::make_shared<metal>(color(0.55, 0.47, 0.14), 0.0);
    auto m_glass1 = std::make_shared<dielectric>(1.5);
    auto m_glass2 = std::make_shared<dielectric>(1.5, color(1,1,1), color(0, 0.7, 0.8));
    auto m_bubble = make_shared<dielectric>(1.00 / 1.50);

    world->add(std::make_shared<sphere>(point3(0.0, -1000.5, -1.0), 1000.0, m_ground));
    world->add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, m_mirror));
    world->add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, m_mirror));
    world->add(std::make_shared<sphere>(point3(0, 0.0, -2), 0.5, m_mirror2));
    world->add(std::make_shared<sphere>(point3(-0.4, 0.2, -0.8), 0.3, m_glass1));
    world->add(std::make_shared<sphere>(point3(-0.4, 0.2, -0.8), 0.2, m_bubble));
    world->add(std::make_shared<sphere>(point3(0.4, 0.2, -0.8), 0.3, m_glass2));
    world->add(std::make_shared<sphere>(point3(0.4, 0.2, -0.8), 0.2, m_bubble));

    return world;
}

std::shared_ptr<hittable_list> Scene4::create() const {
    auto world = std::make_shared<hittable_list>();

    auto m_ground = std::make_shared<lambertian>(color(0.52, 0.37, 0.26));
    auto m_water = std::make_shared<dielectric>(1.33);
    auto m_water2 = std::make_shared<dielectric>(1.33, color(1,1,1), color(0, 0.7, 0.8));
    auto m_bubble = make_shared<dielectric>(1.00 / 1.33);

    world->add(std::make_shared<sphere>(point3(0.0, -1000.5, -1.0), 1000.0, m_ground));

    world->add(std::make_shared<sphere>(point3(-1, 0.2, -0.8), 0.25, m_water));
    world->add(std::make_shared<sphere>(point3(-1, 0.2, -0.8), 0.24, m_bubble));

    world->add(std::make_shared<sphere>(point3(-0.6, 0.3, -1), 0.25, m_water));
    world->add(std::make_shared<sphere>(point3(-0.6, 0.3, -1), 0.24, m_bubble));

    world->add(std::make_shared<sphere>(point3(-0.4, 0, -0.3), 0.3, m_water));
    world->add(std::make_shared<sphere>(point3(-0.4, 0, -0.3), 0.29, m_bubble));

    world->add(std::make_shared<sphere>(point3(-0.3, 0.2, -0.5), 0.2, m_water));
    world->add(std::make_shared<sphere>(point3(-0.3, 0.2, -0.5), 0.19, m_bubble));

    world->add(std::make_shared<sphere>(point3(0.4, 0.4, -0.2), 0.27, m_water2));
    world->add(std::make_shared<sphere>(point3(0.4, 0.4, -0.2), 0.26, m_bubble));

    world->add(std::make_shared<sphere>(point3(0.2, 0.1, -1), 0.2, m_water2));
    world->add(std::make_shared<sphere>(point3(0.2, 0.1, -1), 0.19, m_bubble));

    world->add(std::make_shared<sphere>(point3(0.7, 0.2, -1.2), 0.3, m_water2));
    world->add(std::make_shared<sphere>(point3(0.7, 0.2, -1.2), 0.28, m_bubble));
    return world;
}

std::shared_ptr<hittable_list> Scene5::create() const {
    auto world = std::make_shared<hittable_list>();

    auto m_ground = std::make_shared<lambertian>(color(0.52, 0.37, 0.26));
    auto m_mirror = std::make_shared<metal>(color(0.9, 0.9, 0.9), 0.0);
    auto m_mirror2 = std::make_shared<metal>(color(0.55, 0.47, 0.14), 0.0);

    world->add(std::make_shared<sphere>(point3(0.0, -1000.5, -1.0), 1000.0, m_ground));
    world->add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, m_mirror));
    world->add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, m_mirror));
    world->add(std::make_shared<sphere>(point3(0, 0.0, -2), 0.5, m_mirror2));

    return world;
}
