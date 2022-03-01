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

    double operator[](int i) const
    {
        return e[i];
    }

    double &operator[](int i) { return e[i]; }

    double x() { return e[0]; }
    double y() { return e[1]; }
    double z() { return e[2]; }

    vec3 operator+(vec3 &v) //加法
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];

        return *this;
    }

    vec3 operator*(double t) //乘标量
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 operator/(double t)
    {
        return *this* (1/t);
    }

    double length_squared() //向量大小的平方
    {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    double length()
    {
        return sqrt(length_squared());
    }

    double dot(vec3 &v)
    {
        return e[0]*v.e[0]
            +  e[1]*v.e[1]
            +  e[2]*v.e[2];
    }

    vec3 cross(vec3 &v)
    {
        return vec3(e[1] * v.e[2] - e[2] * v.e[1],
                    e[2] * v.e[0] - e[0] * v.e[2],
                    e[0] * v.e[1] - e[1] * v.e[0]);
    }

    vec3 unit_vector()
    {
        return *this / length();
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

vec3 operator/(double t,const vec3 &v)
{
    return (1/t) *v;
}

vec3 unit_vector(vec3 v)
{
    return v/v.length();
}



using point3 = vec3;
using color = vec3;
#endif