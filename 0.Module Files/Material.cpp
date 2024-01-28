#include"Material.h"

#include"Hittable.h"

bool Lambertian::Scatter(const Ray& incident_ray, const HitRecord& record,
    Color& attenuation, Ray& scattered_ray) const
{
    auto scatter_direction = record.normal + RandomUnitVector3();

    if (scatter_direction.IsNearZero())
    {
        scatter_direction = record.normal;
    }

    attenuation = albedo;
    scattered_ray = Ray(record.intersection_point, scatter_direction);
    return true;
}

bool Metal::Scatter(const Ray& incident_ray, const HitRecord& record,
    Color& attenuation, Ray& scattered_ray) const
{
    auto reflect_direction = Reflect(incident_ray.Direction(), record.normal);
    reflect_direction += fuzz * RandomUnitVector3();
    attenuation = albedo;
    scattered_ray = Ray(record.intersection_point, reflect_direction);
    return Dot(record.normal, scattered_ray.Direction()) > 0;
}

bool Dielectric::Scatter(const Ray& incident_ray, const HitRecord& record,
    Color& attenuation, Ray& scattered_ray) const
{
    auto incident_eta_over_transmitted_eta = record.front_face ? 1. / refractive_index : refractive_index;

    auto incident_direction = incident_ray.Direction();

    auto cos_theta = std::fmin(Dot(-incident_direction, record.normal), 1.);
    auto sin_theta = std::sqrt(1 - cos_theta * cos_theta);

    Vector3 scattered_direction;

    if (incident_eta_over_transmitted_eta * sin_theta > 1. ||
        FresnelInSchlick(cos_theta, incident_eta_over_transmitted_eta) > RandomDouble())
    {
        scattered_direction = Reflect(incident_direction, record.normal);
    }
    else
    {
        scattered_direction = Refract(incident_direction, record.normal, incident_eta_over_transmitted_eta);
    }

    scattered_ray = Ray(record.intersection_point, scattered_direction);
    return true;
}

double Dielectric::FresnelInSchlick(double cos_theta, double incident_eta_over_transmitted_eta)
{
    auto f0 = (1 - incident_eta_over_transmitted_eta) * (1 - incident_eta_over_transmitted_eta) /
        (1 + incident_eta_over_transmitted_eta) / (1 + incident_eta_over_transmitted_eta);
    return f0 + ((1 - f0) * (1 - cos_theta)) * ((1 - cos_theta) * (1 - cos_theta)) *
        ((1 - cos_theta) * (1 - cos_theta)); // F¦È
}