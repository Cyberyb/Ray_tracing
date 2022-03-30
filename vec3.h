#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

class vec3
{
public:
    vec3() : e{0, 0, 0} {}
    vec3(double e1, double e2, double e3) : e{e1, e2, e3} {}

    vec3 operator-() const //返回负值/反方向
    {
        return vec3(-e[0], -e[1], -e[2]);
    }

    double operator[] (int i) const
    {
        return e[i];
    }

    double &operator[](int i) { return e[i]; }

    double x() { return e[0]; }
    double y() { return e[1]; }
    double z() { return e[2]; }

    vec3 operator+=(const vec3 &v) //加法
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];

        return *this;
    }

    vec3 operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 operator/=(const double t)
    {
        return *this *= 1/t;
    }

    double length_squared() const //向量大小的平方
    {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    double length() const
    {
        return sqrt(length_squared());
    }

    static vec3 random()
    {
        return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max)
    {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    bool near_zero() const 
    {
        //如果向量非常贴近于0，则返回true
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        //fabs求浮点数的绝对值   
    }

public:
    double e[3];
};

std::ostream& operator<<(std::ostream &out, vec3 &v)
{
    return out<<v.e[0]<<' '<<v.e[1]<<' '<<v.e[2];
 }

vec3 operator+(const vec3& u,const vec3&v)
{
    return vec3(u.e[0]+v.e[0], u.e[1]+ v.e[1],u.e[2]+v.e[2]);
}

vec3 operator-(const vec3& u,const vec3&v)
{
    return vec3(u.e[0]-v.e[0], u.e[1]- v.e[1],u.e[2]-v.e[2]);
}

vec3 operator*(const vec3 &u,const vec3 &v)
{
    return vec3(u.e[0]*v.e[0], u.e[1]* v.e[1],u.e[2]*v.e[2]);
}
vec3 operator*(double t,const vec3 &v)
{
    return vec3(t * v.e[0], t*v.e[1],t*v.e[2]);
}

vec3 operator*(const vec3 &v,double t)
{
    return t*v;
}

vec3 operator/(const vec3 &v,double t)
{
    return (1/t) *v;
}

vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

double dot(const vec3 &u, const vec3 &v)
{
    return u.e[0]*v.e[0]
        +  u.e[1]*v.e[1]
        +  u.e[2]*v.e[2];
}

vec3 cross(const vec3 &u ,const vec3 &v)
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

vec3 random_in_unit_sphere()
{
    while(true)
    {
        vec3 p = vec3::random(-1, 1);
        if(p.length_squared()>=1)
            continue;
        return p;
    }
}

vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}

vec3 reflect(const vec3& v, const vec3& n)//计算反射光线
{
    return v - 2 * dot(v, n) * n;
}

vec3 refract(const vec3& uv, const vec3&n,double etai_over_etat)
{
    auto cos_theta = fmin(dot(-uv,n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

vec3 random_in_unit_disk()
{
    while (true)
    {
        auto p = vec3(random_double(-1,1), random_double(-1,1),0);
        if(p.length_squared() >= 1) 
            continue;
        return p;
    }
    
}

using point3 = vec3;
using color = vec3;
#endif