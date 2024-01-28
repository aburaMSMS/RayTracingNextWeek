#include"Sphere.h"

bool Sphere::IsHit(const Ray& ray, Interval t_range, HitRecord& hit_record) const
{
    auto ray_origin = ray.Origin();
    auto ray_direction = ray.Direction();
    auto center_to_ray_origin = ray_origin - center;

    auto a = ray_direction.LengthSquared();
    auto half_b = Dot(ray_direction, center_to_ray_origin);
    auto c = center_to_ray_origin.LengthSquared() - radius * radius;

    auto delta = half_b * half_b - a * c;

    if (delta < 0.)
    {
        return false;
    }

    auto sqrt_delta = std::sqrt(delta);
    auto t = (-half_b - sqrt_delta) / a;
    if (!t_range.Surrounds(t))
    {
        t = (-half_b + sqrt_delta) / a;
        if (!t_range.Surrounds(t))
        {
            return false;
        }
    }

    hit_record.t = t;
    hit_record.intersection_point = ray.At(t);
    auto outward_normal = (hit_record.intersection_point - center) / radius;
    hit_record.SetFrontFaceAndNormal(ray, outward_normal);
    hit_record.material = material;

    return true;
}