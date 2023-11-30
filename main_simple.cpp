#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>

#include "rtweekend.h" // vec3.h  : ray.h -- P(t) = A + tb.// at()
#include "color.h"	   // write_color()
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

using namespace std;

// Image FORMAT

/* --- Image -- Output -- Example PPM below ----------------------------------
Color RGB Image in PPM format
P3
# The P3 means color are in ASCII, then 3 columns and 2 rows,
# then 255 for max color, then RGB triplets
3 2
255
255   0   0	  0 255   0       0   0 255
255 255   0	255 255 255  	  0   0   0  ---------------------------------*/

color ray_color(const ray &r, const hittable& world)
{
	// return foreground color (ray hits an object )
	//		(sphere_center, sphere_radius, ray)

	// see if we hit sphere - sphere intersection formula
	// section 5.
	// return hit point, or -1 if not hitting sphere
	hit_record rec;
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + color(1,1,1));
	}

	// return background color
	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	// BLUE blend 1 is white, 0 is no light.1
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	// mostly blue
}

int main()
{
	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;

	int image_height = static_cast<int>(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;
	

	// World
	hittable_list world;

	world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
	world.add(make_shared<sphere>(point3(0,-100,-1), 100));

	// Camera // viewpart -- near clipping plane
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);					// camera_center
	auto horizontal = vec3(viewport_width, 0, 0); // viewport_u
	auto vertical = vec3(0, -viewport_height, 0);  // viewport_v

	auto pixel_delta_hor = horizontal / image_width;
	auto pixel_delta_vert = vertical / image_height;

	//auto lower_left_corner = origin - horizontal / 2	 // x
	//						 - vertical / 2				 // y
	//						 - vec3(0, 0, focal_length); // z (negative)
	auto upper_left_corner = origin - vec3(0, 0, focal_length) - horizontal/2 - vertical/2;
	auto pixel00_loc = upper_left_corner + 0.5 * (pixel_delta_hor + pixel_delta_vert);


	// Render
	const int max_color = 255;
	cout << "P3\n"
		 << image_width << ' ' << image_height << "\n";
	cout << max_color << "\n";

	for (int j = 0; j < image_height; ++j) {
		for(int i = 0; i < image_width; ++i) {
			auto pixel_center = pixel00_loc + (i * pixel_delta_hor) + (j * pixel_delta_vert);
			auto ray_dir = pixel_center - origin;
			ray r (origin, ray_dir);
		}
	}

	cerr << "\nDone.\n";
}
