#ifndef SCENE_H
#define SCENE_H

#include "scene_factory.h"
#include "sphere.h"
#include "material.h"

class Scene : public SceneFactory {
public:
    std::shared_ptr<hittable_list> create() const override;
};

class Scene2: public SceneFactory {
public:
    std::shared_ptr<hittable_list> create() const override;
};

class Scene3: public SceneFactory {
public:
    std::shared_ptr<hittable_list> create() const override;
};

class Scene4: public SceneFactory {
public:
    std::shared_ptr<hittable_list> create() const override;
};

class Scene5: public SceneFactory {
public:
    std::shared_ptr<hittable_list> create() const override;
};

#endif // SCENE_H