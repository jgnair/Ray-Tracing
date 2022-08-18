#ifndef HITLIST_H
#define HITLIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hitlist : public hittable {
    public:
        hitlist() {}
        hitlist(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) { objects.push_back(object); }

        virtual bool hit(
            const ray& r, double min, double max, recordhit& rec) const override;

    public:
        std::vector<shared_ptr<hittable>> objects;
};

bool hitlist::hit(const ray& r, double min, double max, recordhit& rec) const {
    recordhit temp_record;
    bool hashit = false;
    auto closest = max;

    for (const auto& object : objects) {
        if (object->hit(r, min, closest, temp_record)) {
            hashit = true;
            closest = temp_record.d;
            rec = temp_record;
        }
    }

    return hashit;
}

#endif
