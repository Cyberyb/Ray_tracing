#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>
using std::shared_ptr;//智能指针
using std::make_shared;

class hittable_list:public hittable 
{
public:
    hittable_list(){}
    hittable_list(shared_ptr<hittable> object)
    {
        add(object);
    }
    void clear()
    {
        objects.clear();
    }
    void add(shared_ptr<hittable> object)
    {
        objects.push_back(object);
    }

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

public:
    std::vector<shared_ptr<hittable>> objects;
};

//用于判断是否打到了某一个物体上面
bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for(const auto& object:objects)//遍历物品中的每一个物品
    {
        if(object->hit(r,t_min,closest_so_far,temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif