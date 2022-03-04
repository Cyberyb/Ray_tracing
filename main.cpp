#include "constant.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>


color ray_color(const ray& r, const hittable& world)//Get the color of the backgroud
{
    hit_record rec;
    if(world.hit(r,0,infinity,rec))
    {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    //vec3 unit_direction = r.direction().unit_vector();
    auto t = 0.5* (unit_direction.y()+1.0);
    return (1.0 - t)*color(RGB(212,242,231))+ t*color(RGB(0,119,255));
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    //World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));//添加球体
    world.add(make_shared<sphere>(point3(0,-100.5,-1),100));//添加背景球体
    
    //Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0; // set the distance between the projection plane and the projection point to be one unit

    auto origin = point3(0,0,0);
    auto horizontal = vec3(viewport_width,0,0);//viewport x
    auto vertical = vec3(0,viewport_height,0);//viewport y
    auto lower_left_corner = origin - horizontal/2 - vertical/2 -vec3(0,0,focal_length);//

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' '<<std::flush;
        for (int i = 0; i < image_width; ++i) {
            // auto r = double(i) / (image_width-1);
            // auto g = double(j) / (image_height-1);
            // auto b = 0.25;

            // int ir = static_cast<int>(255.999 * r);
            // int ig = static_cast<int>(255.999 * g);
            // int ib = static_cast<int>(255.999 * b);

            // std::cout << ir << ' ' << ig << ' ' << ib << '\n';
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r,world);
            write_color(std::cout,pixel_color);
            
        }
    }
    std::cerr<<"\nDone\n";
}