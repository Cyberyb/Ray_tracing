#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"
#include "vec3.h"

class sphere:public hittable 
{
public:
    sphere(){}
    sphere(point3 cen, double r) : center(cen), radius(r){}

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

public:
    point3 center;
    double radius;
};

bool sphere::hit(const ray &r,double t_min,double t_max,hit_record& rec) const
{
    //t^2 * b·b  +  2tb · (A-C) + (A-C)·(A-C) - r^2
    //a = b·b  b = 2b·(A-C)  c = (A-C)·(A-C)-r^2 
    vec3 oc = r.origin() - center; // 定义P - C
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;//求根公式上部分根号下内容，用于判断正负而不求值
    if(discriminant < 0)
    {
        return false;
    }
    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;//优化后的求根公式  减法
    if(root<t_min || root>t_max) // 超出根的范围
    {
        root = (-half_b + sqrtd) / a; //求根公式  加法
        if(root<t_min || root>t_max)//还是超出范围的话
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    //rec.normal = (rec.p - center) / radius;
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    //打到了
    return true;
}
#endif