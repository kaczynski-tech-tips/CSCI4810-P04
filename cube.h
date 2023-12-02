#ifndef CUBE_H
#define CUBE_H

#include "hittable.h"
#include "vec3.h"
#include <algorithm>

class cube : public hittable {
    private:
        point3 center;
        double radius;
    
    public:
        cube(point3 _center, double _radius) : center(_center), radius(_radius) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 oc = r.origin() - center;
            point3 vn[8];
            auto a = center.x();
            auto b = center.y();
            auto c = center.z();

            vn[0] = point3(a-radius, b-radius, c-radius);
            vn[1] = point3(a-radius, b+radius, c+radius);
            vn[2] = point3(a-radius, b-radius, c+radius);
            vn[3] = point3(a-radius, b+radius, c-radius);
            vn[4] = point3(a+radius, b-radius, c+radius);
            vn[5] = point3(a+radius, b-radius, c-radius);
            vn[6] = point3(a+radius, b+radius, c-radius);
            vn[7] = point3(a+radius, b+radius, c+radius);

            double distance = 0;
            double sum_distance = 0;
            for (int i = 0; i < 8; i++) {
                distance = pow((rec.p.x() - vn[i].x()), 2.0);
                distance += pow((rec.p.y() - vn[i].y()), 2.0);
                distance += pow((rec.p.z() - vn[i].z()), 2.0);
                distance = sqrt(distance);

                sum_distance += distance;
            }
            double determinant = (pow(sum_distance, 2.0)/8) + (2 * pow(radius, 2.0))/3;
            determinant = pow(determinant, 2.0);
            
        }
};

#endif