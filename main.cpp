#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

color ray_color(const ray &r)
{
    return color(0, 0, 0);
}

int main()
{
    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    auto focal_length = 1.0;
    auto viewport_h = 2.0;
    auto viewport_w = viewport_h * (static_cast<double>(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    auto viewport_u = vec3(viewport_w, 0, 0);
    auto viewport_v = vec3(0, -viewport_h, 0);

    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Locate Upper Pixel
    auto viewport_top_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00 = viewport_top_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
           auto pixel_center = pixel00 + (i * pixel_delta_u) + (j * pixel_delta_v);
           auto ray_direction = pixel_center - camera_center;
           ray r(camera_center, ray_direction);

           color pixel_color = ray_color(r);
           write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.\n";
}