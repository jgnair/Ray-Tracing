#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "vec3.h"

constexpr float kEpsilon = 1e-8;

class triangle : public hittable{
    public:
    triangle(const point3& a, const point3& b, const point3& c, shared_ptr<materials> m) : point_a(a), point_b(b), point_c(c), point_n(cross((b-a),(c-a))), mat_ptr(m) {}
    virtual bool hit(const ray& r, double min, double max, recordhit& rec) const override;

    
    public:
    point3 point_a;
    point3 point_b;
    point3 point_c;
    point3 point_n;
    shared_ptr<materials> mat_ptr;
};

bool triangle::hit(const ray& r, double min, double max, recordhit& rec) const {
    auto x = dot(point_n,r.direction());
    if(fabs(x) < kEpsilon){
        return false;
    }
    
    auto d = dot(point_n, point_a);
    auto t = (dot(point_n,r.origin())+d)/x;
    
    if(t < 0){
        return false;
    }

    vec3 P = r.origin() + t * r.direction();
    vec3 C = cross((point_b-point_a),(P-point_a));
    if(dot(point_n,C) < 0 || dot(point_n,C) > 1){
        return false;
    }
    C = cross((point_c-point_b),(P-point_b));
    if(dot(point_n,C) < 0 || dot(point_n,C) > 1){
        return false;
    }
    C = cross((point_a-point_c),(P-point_c));
    if(dot(point_n,C) < 0 || dot(point_n,C) > 1){
        return false;
    }
    rec.d = r.direction().z();
    rec.setnormalface(r, point_n);
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif
