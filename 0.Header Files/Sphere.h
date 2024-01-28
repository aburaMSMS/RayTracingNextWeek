#pragma once

#include "Hittable.h"
#include "Vector3.h"

class Sphere : public Hittable
{
public:
    Sphere(const Point3& _start_center, double _radius, std::shared_ptr<Material> _material)
        : start_center(_start_center), radius(_radius), material(_material) {}

    Sphere(const Point3& _start_center, const Point3& _end_center, double _radius, std::shared_ptr<Material> _material);

    bool IsHit(const Ray& ray, Interval t_range, HitRecord& hit_record) const override;

private:
    Point3 CurrentCenter(double time) const;

private:
    Point3 start_center;
    double radius;
    std::shared_ptr<Material> material;
    Vector3 moving_direction;
};
