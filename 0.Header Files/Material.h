#pragma once

#include"Color.h"
#include"Ray.h"

class HitRecord;

class Material
{
public:
    virtual ~Material() = default;

    virtual bool Scatter(const Ray& incident_ray, const HitRecord& record,
        Color& attenuation, Ray& scattered_ray) const = 0;
};


class Lambertian :public Material
{
public:
    Lambertian(const Color& _albedo) :albedo(_albedo) {}

    bool Scatter(const Ray& incident_ray, const HitRecord& record,
        Color& attenuation, Ray& scattered_ray) const override;

private:
    Color albedo;
};

class Metal : public Material
{
public:
    Metal(const Color& _albedo, double _fuzz = 1.)
        : albedo(_albedo), fuzz(_fuzz < 1 ? _fuzz : 1) {}

    bool Scatter(const Ray& incident_ray, const HitRecord& record,
        Color& attenuation, Ray& scattered_ray) const override;

private:
    Color albedo;
    double fuzz;
};


class Dielectric : public Material 
{
private:
    static double FresnelInSchlick(double cos_theta, double incident_eta_over_transmitted_eta);

public:
    Dielectric(double _refractive_index) :refractive_index(_refractive_index) {}

    bool Scatter(const Ray& incident_ray, const HitRecord& record,
        Color& attenuation, Ray& scattered_ray) const override;

private:
    double refractive_index;
};