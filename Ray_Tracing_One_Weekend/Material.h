#pragma once
#include "hittable.h"
#include "ray.h"
#include "color.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(Ray r_in, RaycastHit rec, Color& attenuation, Ray& scattered)
    {
        return false;
    }
};

class Lambertian : public Material {
public:
    Lambertian(const Color& albedo) : m_albedo(albedo) {}

    bool scatter(Ray r_in, RaycastHit rec, Color& attenuation, Ray& scattered) override
    {
        auto scatter_direction = rec.m_normal + vector3::randomUnitVector();

        if (scatter_direction.nearZero())
            scatter_direction = rec.m_normal;

        scattered = Ray(rec.m_point, scatter_direction);
        attenuation = m_albedo;
        return true;
    }

private:
    Color m_albedo;
};

class Metal : public Material 
{
public:
    Metal(const Color& albedo, float fuzz) : m_albedo(albedo), m_fuzz(fuzz < 1 ? fuzz : 1)  {}

    bool scatter(Ray r_in, RaycastHit rec, Color& attenuation, Ray& scattered) override
    {        
        vec3 reflected = vector3::reflect(r_in.getDirection(), rec.m_normal);
        reflected = reflected.unitVector() + (vector3::randomUnitVector() * m_fuzz);
        scattered = Ray(rec.m_point, reflected);
        attenuation = m_albedo;
        return (scattered.getDirection().dot(rec.m_normal) > 0);
    }

private:
    Color m_albedo;
    float m_fuzz;
};