#if 1

#include <iostream>
#include "global.h"
#include "Camera.h"
#include "HittableList.h"
#include "Sphere.h"
#include "BVH.h"
#include "Quadrilateral.h"

int main()
{
    HittableList world;

    auto red = std::make_shared<Lambertian>(Color(0.65, 0.05, 0.05));
    auto white = std::make_shared<Lambertian>(Color(0.73));
    auto green = std::make_shared<Lambertian>(Color(0.12, 0.45, 0.15));
    auto light = std::make_shared<DiffuseLight>(Color(15.));

    world.Add(std::make_shared<Quadrilateral>(
        Point3{555., 0., 0.}, Vector3{0., 555., 0.}, Vector3{0., 0., 555.}, green));
    world.Add(std::make_shared<Quadrilateral>(
        Point3{0., 0., 0.}, Vector3{0., 555., 0.}, Vector3{0., 0., 555.}, red));
     world.Add(std::make_shared<Quadrilateral>(
         Point3{343., 554., 332.}, Vector3{-130., 0., 0.}, Vector3{0., 0., -105.}, light));
    world.Add(std::make_shared<Quadrilateral>(
        Point3{0., 0., 0.}, Vector3{555., 0., 0.}, Vector3{0., 0., 555.}, white));
    world.Add(std::make_shared<Quadrilateral>(
        Point3{555., 555., 555.}, Vector3{-555., 0., 0.}, Vector3{0., 0., -555.}, white));
    world.Add(std::make_shared<Quadrilateral>(
        Point3{0., 0., 555.}, Vector3{555., 0., 0.}, Vector3{0., 555., 0.}, white));

    
    world.Add(Box(Point3{130., 0., 65.}, Point3{295., 165., 230.}, white));
    world.Add(Box(Point3{265., 0., 295.}, Point3{430., 330., 460.}, white));

    world = HittableList(std::make_shared<BVH>(world));

    Camera camera;

    camera.aspect_ratio = 1.0;
    camera.image_width = 400;
    camera.samples_per_pixel = 200;
    camera.max_depth = 50;
    camera.background = Color{0.};

    camera.vertical_fov = 40.;
    camera.look_from = Point3{278, 278, -800};
    camera.look_at = Point3{278, 278, 0};
    camera.view_up = Vector3{0, 1, 0};

    camera.defocus_angle = 0;

    camera.Render(world);
}

#endif // 1
