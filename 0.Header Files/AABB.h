#pragma once

#include"Interval.h"
#include"Vector3.h"
#include"Ray.h"

class AABB
{
public:
    AABB() {}
    AABB(const Interval& _x, const Interval& _y, const Interval& _z) :x(_x), y(_y), z(_z) {}
    AABB(const Point3& p1, const Point3& p2);
    AABB(const AABB& box1, const AABB& box2);

    const Interval& Axis(int axis_index) const;

    bool IsHit(const Ray& ray, Interval t_range) const;

    AABB Pad() const;
public:
    Interval x, y, z;
};
