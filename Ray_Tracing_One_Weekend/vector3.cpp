#include "vector3.h"

vector3::vector3() : m_x(0.0), m_y(0.0), m_z(0.0) {}

vector3::vector3(float xVal, float yVal, float zVal) : m_x(xVal), m_y(yVal), m_z(zVal) {}

vector3::~vector3() {}

float vector3::x()
{ 
    return this->m_x; 
}

float vector3::y()
{ 
    return this->m_y;
}

float vector3::z()
{ 
    return this->m_z;
}

vector3 vector3::operator-() const 
{ 
    return vector3(-m_x, -m_y, -m_z);
}

vector3 vector3::operator+(const vector3& other) const
{
    return vector3(
        m_x + other.m_x,
        m_y + other.m_y,
        m_z + other.m_z
    );
}

vector3& vector3::operator+=(const vector3& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
    return *this;
}

vector3 vector3::operator-(const vector3& other) const
{
    return vector3(
        m_x - other.m_x,
        m_y - other.m_y,
        m_z - other.m_z
    );
}

vector3& vector3::operator-=(const vector3& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
    return *this;
}

vector3 vector3::operator*(float scale) const
{
    return vector3(
        scale * m_x,
        scale * m_y,
        scale * m_z
    );
}

vector3& vector3::operator*=(float scale)
{
    m_x *= scale;
    m_y *= scale;
    m_z *= scale;
    return *this;
}

vector3 vector3::operator/(float divisor) const
{
   return vector3(
        m_x / divisor,
        m_y / divisor,
        m_z / divisor
    );
}

vector3& vector3::operator/=(float divisor)
{
    m_x /= divisor;
    m_y /= divisor;
    m_z /= divisor;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const vector3& vec)
{
    os << "(" << vec.m_x << ", " << vec.m_y << ", " << vec.m_z << ")";
    return os;
}

float vector3::length() const
{
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

float vector3::lenghtSquared() const
{
    return m_x * m_x + m_y * m_y + m_z * m_z;
}

float vector3::dot(const vector3 other) const
{
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

vector3 vector3::cross(const vector3 other) const
{
    return vector3(
        m_y * other.m_z - m_z * other.m_y,
        m_z * other.m_x - m_x * other.m_z,
        m_x * other.m_y - m_y * other.m_x
    );
}

vector3 vector3::unitVector() const
{
    float len = length();
    if (len != 0) 
    {
        return vector3(
            m_x / len,
            m_y / len,
            m_z / len
        );
    }

    return *this;
}
