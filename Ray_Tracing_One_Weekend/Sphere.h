#pragma once
#include "Hittable.h"
#include "vector3.h"

class Sphere : public Hittable
{
public:
	Sphere(const vec3& center, float radius, std::shared_ptr<Material> material);

	bool hit(Ray r, Interval ray_t, RaycastHit& rec) const override;

private:
	vec3 m_center;
	float m_radius;
	std::shared_ptr<Material> m_material;
};

