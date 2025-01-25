#pragma once
#include "vector3.h"

class Ray
{
public:
	Ray();
	Ray(const vector3& origin, const vector3& direction);
	~Ray();

	vector3 getOrigin();
	vector3 getDirection();
	vector3 at(float timeStep);

private:
	vector3 m_origin;
	vector3 m_direction;
};

