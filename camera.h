#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "color.h"
#include "hittable.h"
#include <iostream>

class camera
{

public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;

    void render(const hittable &world)
    {
        initialize();
        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; ++j)
        {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; ++sample)
                {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, world);
                }
                write_color(std::cout, pixel_color, samples_per_pixel);
            }
        }

        std::clog << "\rDone.\n";
    }

private:
    int image_height;
    point3 center;
    point3 pixel00;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    void initialize()
    {
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        center = point3(0, 0, 0);
        auto focal_length = 1.0;
        auto viewport_h = 2.0;
        auto viewport_w = viewport_h * (static_cast<double>(image_width) / image_height);

        auto viewport_u = vec3(viewport_w, 0, 0);
        auto viewport_v = vec3(0, -viewport_h, 0);

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Locate Upper Pixel
        auto viewport_top_left = center - vec3(0, 0, focal_length) - (viewport_u / 2) - (viewport_v / 2);
        pixel00 = viewport_top_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    color ray_color(const ray &r, const hittable &world) const
    {
        hit_record rec;

        if (world.hit(r, interval(0, infinity), rec))
        {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }

    ray get_ray(int i, int j) const
    {
        // get random camera ray
        auto pixel_center = pixel00 + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto pixel_sample = pixel_center + pixel_sample_square();

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 pixel_sample_square() const
    {
        // returns random point in square surrounding origin pixel
        auto px = -0.5 + random_double();
        auto py = -0.5 + random_double();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }
};

#endif