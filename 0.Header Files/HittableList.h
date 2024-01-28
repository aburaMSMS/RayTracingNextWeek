#pragma once

#include"Hittable.h"
#include"Interval.h"

#include<vector>
#include<memory>

class HittableList :public Hittable
{
public:
    std::vector<std::shared_ptr<Hittable>> objects;

    HittableList() {}

    void Clear();

    void Add(std::shared_ptr<Hittable> object);

    bool IsHit(const Ray& ray, Interval t_range, HitRecord& hit_record) const override;
};