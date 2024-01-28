#pragma once

#include "Hittable.h"
#include "Vector3.h"

class Sphere : public Hittable
{
public:
    Sphere(const Point3& _center, double _radius, std::shared_ptr<Material> _material)
        : center(_center), radius(_radius), material(_material) {}

    bool IsHit(const Ray& ray, Interval t_range, HitRecord& hit_record) const override;

private:
    Point3 center;
    double radius;
    std::shared_ptr<Material> material;
};
