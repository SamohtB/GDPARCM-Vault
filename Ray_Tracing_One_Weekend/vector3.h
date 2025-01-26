#pragma once
#include <iostream>
#include <cmath>

class vector3
{
public:
	vector3();
	vector3(float x, float y, float z);
	~vector3();

	float x();
	float y();
	float z();

	vector3 operator-() const;

	vector3 operator+(const vector3& vector) const;
	vector3& operator+=(const vector3& vector);

	vector3 operator-(const vector3& vector) const;
	vector3& operator-=(const vector3& vector);

	vector3 operator*(const float scale) const;
	vector3& operator*=(const float scale);

	vector3 operator/(const float dividend) const;
	vector3& operator/=(const float dividend);

	float length() const;
	float lenghtSquared() const;
	float dot(const vector3 vector) const;
	vector3 cross(const vector3 vector) const;
	vector3 unitVector() const;
		
	static vector3 random();
	static vector3 random(float min, float max);
	static vector3 randomUnitVector();
	static vector3 randomOnHemisphere(const vector3& normal);

private:
	float m_x;
	float m_y;
	float m_z;

	friend std::ostream& operator<<(std::ostream& os, const vector3& vec);
};

using vec3 = vector3;

