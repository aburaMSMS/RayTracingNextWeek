#if 0

#include<iostream>
#include"global.h"
#include"Camera.h"
#include"HittableList.h"
#include"Quadrilateral.h"
#include"BVH.h"

int main()
{
    HittableList world;

    auto left_red = std::make_shared<Lambertian>(Color(1., 0.2, 0.2));
    auto back_green = std::make_shared<Lambertian>(Color(0.2, 1., 0.2));
    auto right_blue = std::make_shared<Lambertian>(Color(0.2, 0.2, 1.));
    auto upper_orange = std::make_shared<Lambertian>(Color(1., 0.5, 0.));
    auto lower_teal = std::make_shared<Lambertian>(Color(0.2, 0.8, 0.8));

    world.Add(std::make_shared<Quadrilateral>
        (Point3(-3., -2., 5.), Vector3(0., 0., -4.), Vector3(0., 4., 0.), left_red));
    world.Add(std::make_shared<Quadrilateral>
        (Point3(-2., -2., 0.), Vector3(4., 0., 0.), Vector3(0., 4., 0.), back_green));
    world.Add(std::make_shared<Quadrilateral>
        (Point3(3., -2., 1.), Vector3(0., 0., 4.), Vector3(0., 4., 0.), right_blue));
    world.Add(std::make_shared<Quadrilateral>
        (Point3(-2., 3., 1.), Vector3(4., 0., 0.), Vector3(0., 0., 4.), upper_orange));
    world.Add(std::make_shared<Quadrilateral>
        (Point3(-2., -3., 5.), Vector3(4., 0., 0.), Vector3(0., 0., -4.), lower_teal));

    Camera camera;

    camera.aspect_ratio = 1.;
    camera.image_width = 400;
    camera.samples_per_pixel = 100;
    camera.max_depth = 50;

    camera.vertical_fov = 80.;
    camera.look_from = Point3(0., 0., 9.);
    camera.look_at = Point3(0.);
    camera.view_up = Vector3(0., 1, 0.);

    camera.defocus_angle = 0.;

    camera.Render(world);
}

#endif // 1
