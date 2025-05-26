#include "scene.h"

std::shared_ptr<hittable_list> Scene::create() const {
    auto world = std::make_shared<hittable_list>();

    auto m_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
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
