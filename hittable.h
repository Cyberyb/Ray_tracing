#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
struct hit_record
{
    point3 p;//交点
    vec3 normal;//法线
    double t;//根
    bool front_face; //Tell that the ray is in the sphere or outside

    //光线在外不变，光线在内法线反向
    void set_face_normal(const ray& r,const vec3& outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable
{
    public:
        virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;
};

#endif