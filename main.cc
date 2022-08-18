#include "utility.h"
#include "color.h"
#include "hitlist.h"
#include "sphere.h"
#include "camera.h"
#include "materials.h"
#include "triangle.h"

#include <iostream>
using namespace std;

color ray_color(const ray& r, hittable& world, int depth){
	recordhit rec;
	if (depth <= 0){
        return color(0,0,0);
	}
    if (world.hit(r, 0.001, infinity, rec)) {
        ray scatteredray;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scatteredray))
            return attenuation * ray_color(scatteredray, world, depth-1);
        return color(0,0,0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main(){
	const auto aspect_ratio = 16.0/9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width/aspect_ratio);
	const int pixelsamples = 100;
	const int maxdepth = 50;

	hitlist world;

	auto ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto lambertian_sphere = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto dielectric_sphere = make_shared<dielectric>(1.5);
	auto specular_sphere = make_shared<specular>(color(0.8, 0.6, 0.2), 0.0);

	world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, ground));
	world.add(make_shared<sphere>(point3( 0.0, 0.0, -1.0),   0.5, lambertian_sphere));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0),   0.5, specular_sphere));
	world.add(make_shared<sphere>(point3( 1.0, 0.0, -1.0),   0.5, dielectric_sphere));

	camera cam(point3(3,1,1), point3(0,0,-1), vec3(0,1,0), 50, aspect_ratio);

	cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height-1; j >=0; j--){
		for(int i = 0; i < image_width; i++){
			color pixel_color(0, 0, 0);
            for (int s = 0; s < pixelsamples; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, maxdepth);
            }
            write_color(std::cout, pixel_color, pixelsamples);
		}
	}
	return 0;
}
