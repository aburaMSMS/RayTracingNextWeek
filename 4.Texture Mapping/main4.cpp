#if 0

#include<iostream>
#include"global.h"
#include"Camera.h"
#include"HittableList.h"
#include"Sphere.h"
#include"BVH.h"

int main()
{
    auto earth_texture = std::make_shared<ImageTexture>("earthmap.jpg");
    auto earth_surface = std::make_shared<Lambertian>(earth_texture);
    auto globe = std::make_shared<Sphere>(Point3(0, 0, 0), 2, earth_surface);

    Camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 800;
    camera.samples_per_pixel = 500;
    camera.max_depth = 50;

    camera.vertical_fov = 20;
    camera.look_from = Point3(0, 6, -12);
    camera.look_at = Point3(0, 0, 0);
    camera.view_up = Vector3(0, 1, 0);

    camera.defocus_angle = 0;

    camera.Render(HittableList(globe));
}

#endif // 1
