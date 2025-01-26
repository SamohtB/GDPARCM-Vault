#include "Sphere.h"

Sphere::Sphere(const vec3& center, float radius, std::shared_ptr<Material> material) 
    : m_center(center), m_radius(static_cast<float>(std::fmax(0, radius))), m_material(material) {}

bool Sphere::hit(Ray r, Interval ray_t, RaycastHit& rec) const
{
    vec3 oc = m_center - r.getOrigin();
    float a = r.getDirection().lenghtSquared();
    float h = r.getDirection().dot(oc);
    float c = oc.lenghtSquared() - m_radius * m_radius;
    float discriminant = h * h - a * c;

    if (discriminant < 0)
    {
        return false;
    }

    auto sqrtd = std::sqrt(discriminant);

    auto root = (h - sqrtd) / a;
    if (!ray_t.surrounds(root)) 
    {
        root = (h + sqrtd) / a;
        if (!ray_t.surrounds(root))
            return false;
    }

    rec.m_t = root;
    rec.m_point = r.at(rec.m_t);
    vector3 outward_normal = (rec.m_point - m_center) / m_radius;
    rec.setFaceNormal(r, outward_normal);
    rec.m_material = m_material;

    return true;
}
