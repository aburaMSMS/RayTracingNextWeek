#if 1

#include<iostream>
#include"global.h"
#include"Camera.h"
#include"HittableList.h"
#include"Sphere.h"
#include"BVH.h"
#include"Quadrilateral.h"

int main()
{
    HittableList world;

    auto pertext = std::make_shared<NoiseTexture>(4.);
    world.Add(std::make_shared<Sphere>(Point3{ 0., -1000., 0. }, 1000.,
        std::make_shared<Lambertian>(pertext)));
    world.Add(std::make_shared<Sphere>(Point3{ 0., 2., 0. }, 2., std::make_shared<Lambertian>(pertext)));

    auto diffuse_light = std::make_shared<DiffuseLight>(Color(4.));
    world.Add(std::make_shared<Sphere>(Point3{ 0., 7., 0. }, 2, diffuse_light));
    world.Add(std::make_shared<Quadrilateral>(Point3{ 3., 1., -2. }, Vector3{ 2., 0., 0. },
        Vector3{ 0., 2., 0. }, diffuse_light));

    Camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 800;
    camera.samples_per_pixel = 200;
    camera.max_depth = 50;
    camera.background = Color{ 0. };

    camera.vertical_fov = 20.;
    camera.look_from = Point3{ 26., 3., 6. };
    camera.look_at = Point3{ 0. ,2., 0. };
    camera.view_up = Vector3{ 0., 1, 0. };

    camera.defocus_angle = 0.;


    camera.Render(world);
}

#endif // 1
