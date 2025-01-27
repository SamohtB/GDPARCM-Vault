#pragma once
#include "hittable.h"
#include "ray.h"
#include "color.h"
#include "Utilities.h"

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

class Dielectric : public Material {
public:
    Dielectric(float refraction_index) : m_refraction_index(refraction_index) {}

    bool scatter(Ray r_in, RaycastHit rec, Color& attenuation, Ray& scattered) override
    {
        attenuation = Color(1.0f, 1.0f, 1.0f);
        float ri = rec.m_is_front_face ? (1.0f / m_refraction_index) : m_refraction_index;

        vec3 unit_direction = r_in.getDirection().unitVector();
        float cos_theta = std::fmin(-unit_direction.dot(rec.m_normal), 1.0f);
        float sin_theta = std::sqrt(1.0f - cos_theta * cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0f;
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta, ri) > random_float())
            direction = vector3::reflect(unit_direction, rec.m_normal);
        else
            direction = vector3::refract(unit_direction, rec.m_normal, ri);

        scattered = Ray(rec.m_point, direction);
        return true;
    }

private:
    float m_refraction_index;

    static float reflectance(float cosine, float refraction_index) 
    {
        float r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1.f - cosine), 5.f);
    }
};