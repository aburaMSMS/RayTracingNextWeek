#pragma once

#include "Ray.h"
#include "Interval.h"
#include "AABB.h"

class Material;

class HitRecord
{
public:
    Point3 intersection_point;
    Vector3 normal;
    double t = 0.;
    std::shared_ptr<Material> material;
    double u = 0.;
    double v = 0.;
    bool front_face = true;

    void SetFrontFaceAndNormal(const Ray &ray, const Vector3 &outward_normal);
};

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool IsHit(const Ray &ray, Interval t_range, HitRecord &hit_record) const = 0;

    virtual AABB BoundingBox() const = 0;
};

class Translate : public Hittable
{
public:
    Translate(std::shared_ptr<Hittable> _object, const Vector3 &_offset);

    bool IsHit(const Ray &ray, Interval t_range, HitRecord &hit_record) const override;

    AABB BoundingBox() const override;

private:
    std::shared_ptr<Hittable> object;
    Vector3 offset;
    AABB bounding_box;
};

class Rotate : public Hittable
{
public:
    Rotate(std::shared_ptr<Hittable> _object, double theta, int _axis_index)
        : Rotate(_object, theta, (_axis_index + 1) % 3, (_axis_index + 2) % 3) {}
    Rotate(std::shared_ptr<Hittable> _object, double theta, int _from_axis, int _to_axis);

    bool IsHit(const Ray &ray, Interval t_range, HitRecord &hit_record) const override;

    AABB BoundingBox() const override;

private:
    void RotatePoint3(Point3 &point, bool rotate_direction = true) const;

private:
    std::shared_ptr<Hittable> object;
    double cos_theta;
    double sin_theta;
    int from_axis;
    int to_axis;
    AABB bounding_box;
};
