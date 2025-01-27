#include "vector3.h"
#include "Utilities.h"

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

vector3 vector3::operator*(const vector3& vector) const
{
    return vector3(
        m_x * vector.m_x,
        m_y * vector.m_y,
        m_z * vector.m_z
    );
}

vector3& vector3::operator*=(const vector3& vector)
{
    m_x *= vector.m_x;
    m_y *= vector.m_y;
    m_z *= vector.m_z;

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

bool vector3::nearZero() const
{
    auto s = 1e-8f;
    return (std::fabs(m_x) < s) && (std::fabs(m_y) < s) && (std::fabs(m_z) < s);
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

vector3 vector3::random() 
{
    return vec3(random_float(), random_float(), random_float());
}

vector3 vector3::random(float min, float max) 
{
    return vec3(random_float(min, max), random_float(min, max), random_float(min, max));
}

vector3 vector3::randomUnitVector()
{
    while (true) 
    {
        vector3 p = vec3::random(-1, 1);
        float lensq = p.lenghtSquared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

vector3 vector3::randomOnHemisphere(const vector3& normal)
{
    vec3 on_unit_sphere = vector3::randomUnitVector();
    if (on_unit_sphere.dot(normal) > 0.0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

vector3 vector3::reflect(const vector3& vector, const vector3& normal)
{
    return vector - normal * (vector.dot(normal) * 2.f);
}

vector3 vector3::refract(const vector3& uv, const vector3& n, float etai_over_eta)
{
    float cos_theta = std::fmin(-uv.dot(n), 1.0f);
    vec3 r_out_perp = (uv + n * cos_theta) * etai_over_eta;
    vec3 r_out_parallel = n * (float) -std::sqrt(std::fabs(1.0 - r_out_perp.lenghtSquared()));
    return r_out_perp + r_out_parallel;
}