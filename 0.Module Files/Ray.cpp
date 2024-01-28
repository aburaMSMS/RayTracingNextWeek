#include"Ray.h"

Point3 Ray::Origin() const
{
    return origin;
}

Vector3 Ray::Direction() const
{
    return direction;
}


Point3 Ray::At(double t) const
{
    return origin + t * direction;
}