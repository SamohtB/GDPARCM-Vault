#pragma once
#include "Hittable.h"
#include "vector3.h"

class Sphere : public Hittable
{
public:
	Sphere(const vec3& center, float radius);

	bool hit(Ray r, Interval ray_t, RaycastHit& rec) const override;

private:
	vec3 m_center;
	float m_radius;
};

