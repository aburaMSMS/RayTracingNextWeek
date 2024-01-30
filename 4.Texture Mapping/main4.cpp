#if 1

#include<iostream>
#include"global.h"
#include"Camera.h"
#include"HittableList.h"
#include"Sphere.h"
#include"BVH.h"
#include"Texture.h"

int main()
{
    HittableList world;

    auto checker = std::make_shared<CheckerTexture>(
        2, Color(0.7, 0.3, 0.6), Color(0.9, 1.0, 0.8));

    world.Add(std::make_shared<Sphere>(Point3(0., -10., 0.), 10.,
        std::make_shared<Lambertian>(checker)));
    world.Add(std::make_shared<Sphere>(Point3(0., 10., 0.), 10.,
        std::make_shared<Lambertian>(checker)));

    Camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 400;
    camera.samples_per_pixel = 100;
    camera.max_depth = 50;

    camera.vertical_fov = 20;
    camera.look_from = Point3(13, 2, 3);
    camera.look_at = Point3(0, 0, 0);
    camera.view_up = Vector3(0, 1, 0);

    camera.defocus_angle = 0;

    camera.Render(world);
}

#endif // 1
