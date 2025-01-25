#include "ray.h"

Ray::Ray() {}

Ray::Ray(const vector3& origin, const vector3& direction) : m_origin(origin), m_direction(direction) {}

Ray::~Ray() {}

vector3 Ray::getOrigin()
{
	return m_origin;
}

vector3 Ray::getDirection()
{
	return m_direction;
}

vector3 Ray::at(float timeStep)
{
	return m_origin + (m_direction * timeStep);
}