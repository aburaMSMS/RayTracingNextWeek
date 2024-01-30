#pragma once

#include"Ray.h"
#include"Interval.h"
#include"AABB.h"

class Material;

class HitRecord
{
public:
    Point3 intersection_point;
    Vector3 normal;
    double t = 0.;
    std::shared_ptr<Material> material;
    bool front_face = true;

    void SetFrontFaceAndNormal(const Ray& ray, const Vector3& outward_normal);
};

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool IsHit(const Ray& ray, Interval t_range, HitRecord& hit_record) const = 0;

    virtual AABB BoundingBox() const = 0;
};