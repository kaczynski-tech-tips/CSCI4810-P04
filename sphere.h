#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
    sphere(point3 _center, double _radius) : center(_center), radius(_radius) {}

    bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const override
    {
        vec3 oc = r.origin() - center;
        auto a = dot(r.direction(), r.direction());
        auto b = 2.0 * dot(oc, r.direction());
        auto c = dot(oc, oc) - radius * radius;

        auto discriminant = b*b - a*c;
        if (discriminant < 0) return false;
        auto sqrtd = sqrt(discriminant);

        //Find the nearest root
        auto root = (-b - sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root) {
            root = (-b + sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root) {
                return false;
            }
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

private:
    point3 center;
    double radius;
};

#endif