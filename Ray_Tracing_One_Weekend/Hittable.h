#pragma once
#include "ray.h"
#include "Interval.h"

class RaycastHit 
{
public:
    vec3 m_point;
    vec3 m_normal;
    float m_t;
    bool m_isFrontFace;

    void setFaceNormal(Ray r, const vec3& outward_normal)
    {
        m_isFrontFace = r.getDirection().dot(outward_normal) < 0;
        m_normal = m_isFrontFace ? outward_normal : -outward_normal;
    }
};

class Hittable 
{
public:
    virtual ~Hittable() = default;

    virtual bool hit(Ray r, Interval ray_t, RaycastHit& rec) const = 0;
};
