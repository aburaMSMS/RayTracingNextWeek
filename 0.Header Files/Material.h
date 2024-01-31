#pragma once

#include"Color.h"
#include"Ray.h"
#include"Texture.h"

class HitRecord;

class Material
{
public:
    virtual ~Material() = default;

    virtual Color Emit(double u, double v, const Point3& point) const;

    virtual bool Scatter(const Ray& incident_ray, const HitRecord& record,
        Color& attenuation, Ray& scattered_ray) const = 0;
};


class Lambertian :public Material
{
public:
    Lambertian(const Color& _albedo) :albedo(std::make_shared<SolidColor>(_albedo)) {}

    Lambertian(const std::shared_ptr<Texture> texture) :albedo(texture) {}

    bool Scatter(const Ray& incident_ray, const HitRecord& record,
        Color& attenuation, Ray& scattered_ray) const override;

private:
    std::shared_ptr<Texture> albedo;
};

class Metal : public Material
{
public:
    Metal(const Color& _albedo, double _fuzz = 0.)
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

class DiffuseLight :public Material
{
public:
    DiffuseLight(std::shared_ptr<Texture> _light_texture) :light_texture(_light_texture) {}
    DiffuseLight(Color color = { 0. }) :light_texture(std::make_shared<SolidColor>(color)) {}

    Color Emit(double u, double v, const Point3& point) const;

    bool Scatter(const Ray& incident_ray, const HitRecord& record,
        Color& attenuation, Ray& scattered_ray) const override;
private:
    std::shared_ptr<Texture> light_texture;
};