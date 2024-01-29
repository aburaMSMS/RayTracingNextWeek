#if 1

#include"global.h"
#include"Camera.h"
#include"HittableList.h"
#include"Sphere.h"


int main()
{
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_material = RandomDouble();
            Point3 center(a + 0.6 * RandomDouble(), 0.2, b + 0.6 * RandomDouble());

            if ((center - Point3(4., 1., 0.)).Length() >= 1.2
                && (center - Point3(-4., 1., 0.)).Length() >= 1.2
                && (center - Point3(0., 1., 0.)).Length() >= 1.2)
            {
                std::shared_ptr<Material> sphere_material;

                if (choose_material < 0.5)
                {
                    // Diffuse
                    auto albedo = Color::Random() * Color::Random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    auto end_center = center + Vector3(0., RandomDouble(0, 0.4), 0.);
                    world.Add(std::make_shared<Sphere>(center, end_center, 0.2, sphere_material));
                }
                else if (choose_material < 0.9) {
                    // Metal
                    auto albedo = Color::Random(0.3, 1);
                    auto fuzz = RandomDouble(0, 0.1);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // Glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.Add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.16, 0.67, 0.54));
    world.Add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);
    world.Add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    Camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 400;
    camera.samples_per_pixel = 100;
    camera.max_depth = 50;

    camera.vertical_fov = 20.;
    camera.look_from = Point3(13, 2, 3);
    camera.look_at = Point3(0, 0, 0);
    camera.view_up = Vector3(0, 1, 0);

    camera.defocus_angle = 0.02;
    camera.focus_distance = 10.;

    camera.Render(world);
}

#endif // 1
