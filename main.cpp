#include "color.h"
#include "vec3.h"
#include "ray.h"
#include <iostream>

color ray_color(const ray& r)//Get the color of the backgroud
{
    vec3 unit_direction = unit_vector(r.direction());
    //vec3 unit_direction = r.direction().unit_vector();
    auto t = 0.5* (unit_direction.y()+1.0);
    return (1.0 - t)*color(0.59,0.58,0.94)+ t*color(0.98,0.78,0.83);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

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
            color pixel_color = ray_color(r);
            write_color(std::cout,pixel_color);
            
        }
    }
    std::cerr<<"\nDone\n";
}