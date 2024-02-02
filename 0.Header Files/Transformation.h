#pragma once

#include "Hittable.h"

/* class Transformation */
class Transformation : public Hittable
{
protected:
    Transformation(std::shared_ptr<Hittable> _object) : object(_object) {}

protected:
    std::shared_ptr<Hittable> object;
};

/* class Translate */
class Translate : public Transformation
{
public:
    Translate(std::shared_ptr<Hittable> _object, const Vector3 &_offset);

    bool IsHit(const Ray &ray, Interval t_range, HitRecord &hit_record) const override;

private:
    Vector3 offset;
};

/* class Rotate */
class Rotate : public Transformation
{
public:
    Rotate(std::shared_ptr<Hittable> _object, double theta, int _axis_index)
        : Rotate(_object, theta, (_axis_index + 1) % 3, (_axis_index + 2) % 3) {}
    Rotate(std::shared_ptr<Hittable> _object, double theta, int _from_axis, int _to_axis);

    bool IsHit(const Ray &ray, Interval t_range, HitRecord &hit_record) const override;

private:
    void RotatePoint3(Point3 &point, bool rotate_direction = true) const;

private:
    double cos_theta;
    double sin_theta;
    int from_axis;
    int to_axis;
};

/* Scale */
class Scale : public Transformation
{
public:
    Scale(std::shared_ptr<Hittable> _object, double _scale_rate);

    bool IsHit(const Ray &ray, Interval t_range, HitRecord &hit_record) const override;

private:
    double scale_rate;
};
