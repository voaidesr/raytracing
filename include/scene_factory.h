#ifndef SCENE_FACTORY_H
#define SCENE_FACTORY_H

#include <memory>
#include "hittable_list.h"

class SceneFactory {
public:
    virtual ~SceneFactory() = default;
    virtual std::shared_ptr<hittable_list> create() const = 0;
};

#endif
