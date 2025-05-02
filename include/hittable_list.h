#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "utils.h"

#include "hittable.h"

class hittable_list : public hittable {
    std::vector<shared_ptr<hittable>> objects;
public:
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object);

    void clear();
    void add(shared_ptr<hittable> object);
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};

#endif