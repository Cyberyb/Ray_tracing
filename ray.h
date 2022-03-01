#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class ray 
{
public:
    ray(){}
    ray(const point3& orgin,const vec3& direction)
        :orig(orgin),dir(direction)
    {}

    point3 origin() const {return orig;}
    vec3 direction() const {return dir;}

    point3 at(double t) const
    {
        return orig + t * dir;
    }

private:
    point3 orig;
    vec3 dir;
};



#endif