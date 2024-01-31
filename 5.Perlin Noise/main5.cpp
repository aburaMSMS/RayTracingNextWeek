#if 0

#include<iostream>
#include"global.h"
#include"Camera.h"
#include"HittableList.h"
#include"Sphere.h"
#include"BVH.h"

int main()
{
    HittableList world;

    auto pertext = std::make_shared<NoiseTexture>(4.);
    world.Add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, std::make_shared<Lambertian>(pertext)));
    world.Add(std::make_shared<Sphere>(Point3(0, 2, 0), 2, std::make_shared<Lambertian>(pertext)));

    Camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 400;
    camera.samples_per_pixel = 100;
    camera.max_depth = 50;

    camera.vertical_fov = 20.;
    camera.look_from = Point3(13., 2., 3.);
    camera.look_at = Point3(0.);
    camera.view_up = Vector3(0., 1, 0.);

    camera.defocus_angle = 0.;

    camera.Render(world);
}

#endif // 1
