#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere() {}
        sphere(point3 p, double r, shared_ptr<materials> m) : center(p), radius(r), mat_ptr(m) {};

        virtual bool hit(
            const ray& r, double min, double max, recordhit& rec) const override;

    public:
        point3 center;
        double radius;
        shared_ptr<materials> mat_ptr;
};

bool sphere::hit(const ray& r, double min, double max, recordhit& rec) const {
    vec3 v = r.origin() - center;
    auto a = r.direction().length_squared();
    auto b = dot(v, r.direction());
    auto c = v.length_squared() - radius*radius;

    auto discriminant = b*b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    auto root = (-b - sqrtd) / a;
    if (root < min || max < root) {
        root = (-b + sqrtd) / a;
        if (root < min || max < root)
            return false;
    }

    rec.d = root;
    rec.p = r.at(rec.d);
    vec3 normalout = (rec.p - center) / radius;
    rec.setnormalface(r, normalout);
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif
