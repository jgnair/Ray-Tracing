#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class materials;

struct recordhit {
    point3 p;
    vec3 normal;
    shared_ptr<materials> mat_ptr;
    double d;
    bool front;

    inline void setnormalface(const ray& r, const vec3& v) {
        front = dot(r.direction(), v) < 0;
        normal = front ? v :-v;
    }
};

class hittable {
    public:
        virtual bool hit(const ray& r, double min, double max, recordhit& rec) const = 0;
};

#endif
