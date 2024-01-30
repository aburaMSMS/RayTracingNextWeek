#include"Vector3.h"

Vector3 Reflect(const Vector3& incident_direction, const Vector3& normal)
{
    return incident_direction - 2 * Dot(incident_direction, normal) * normal;
}