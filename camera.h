#ifndef CAMERA_H
#define CAMERA_H

#include "utility.h"

class camera {
    public:
        camera(
            point3 lookfrom,
            point3 lookat,
            vec3 vup,
            double vfov,
            double aspect_ratio
        ) {
            auto theta = degrees_to_radians(vfov);
            auto viewport_height = 2.0 * tan(theta/2);
            auto viewport_width = aspect_ratio * viewport_height;
            
            auto a = unit_vector(lookfrom - lookat);
            auto b = unit_vector(cross(vup,a));
            auto c = cross(a, b);

            origin = lookfrom;
            horizontal = viewport_width * b;
            vertical = viewport_height * c;
            lower_left_corner = origin - horizontal/2 - vertical/2 - a;
        }

        ray get_ray(double x, double y) const {
            return ray(origin, lower_left_corner + x*horizontal + y*vertical - origin);
        }

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
};
#endif
