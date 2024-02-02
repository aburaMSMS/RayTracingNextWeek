#pragma once

#include "Hittable.h"
#include "Vector3.h"
#include "Material.h"
#include "AABB.h"
#include "HittableList.h"

class Quadrilateral : public Hittable
{
public:
    Quadrilateral(const Point3 &_first_vertex, const Vector3 &u, const Vector3 &v, std::shared_ptr<Material> _material);

    bool IsHit(const Ray &ray, Interval t_range, HitRecord &hit_record) const;

private:
    Point3 first_vertex;
    Vector3 u, v;
    std::shared_ptr<Material> material;
    Vector3 normal;
    double d;  // ax + by + cz = d
    Vector3 w; // α = w⋅(p×v) β = w⋅(u×p)
};

std::shared_ptr<HittableList> Box(const Point3 &point1, const Point3 &point2,
                                  std::shared_ptr<Material> material);
