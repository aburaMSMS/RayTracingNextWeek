#include "Hittable.h"

void HitRecord::SetFrontFaceAndNormal(const Ray &ray, const Vector3 &outward_normal)
{
    front_face = Dot(ray.Direction(), outward_normal) < 0.;
    normal = front_face ? outward_normal : -outward_normal;
}

Translate::Translate(std::shared_ptr<Hittable> _object, const Vector3 &_offset)
    : object(_object), offset(_offset)
{
    bounding_box = object->BoundingBox() + offset;
}

bool Translate::IsHit(const Ray &ray, Interval t_range, HitRecord &hit_record) const
{
    Ray offset_ray{ray.Origin() - offset, ray.Direction()};

    if (!object->IsHit(offset_ray, t_range, hit_record))
    {
        return false;
    }

    hit_record.intersection_point += offset;

    return true;
}

AABB Translate::BoundingBox() const
{
    return bounding_box;
}
