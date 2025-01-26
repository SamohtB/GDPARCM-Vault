#include "Camera.h"

void Camera::render(const Hittable& world)
{
    initialize();

    std::cout << "P3\n" << m_image_width << ' ' << m_image_height << "\n255\n";

    for (int j = 0; j < m_image_height; j++) 
    {
        std::clog << "\rScanlines remaining: " << (m_image_height - j) << ' ' << std::flush;
        for (int i = 0; i < m_image_width; i++) 
        {
            auto pixel_center = m_pixel00_loc + (m_pixel_delta_u * i) + (m_pixel_delta_v * j);
            auto ray_direction = pixel_center - m_center;
            Ray r(m_center, ray_direction);

            Color pixel_color = rayColor(r, world);
            ColorUtils::writeColor(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}

void Camera::initialize()
{
    m_image_height = int(m_image_width / m_aspect_ratio);
    m_image_height = (m_image_height < 1) ? 1 : m_image_height;

    m_center = vector3(0.f, 0.f, 0.f);

    // Determine viewport dimensions.
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (float(m_image_width) / m_image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    m_pixel_delta_u = viewport_u / m_image_width;
    m_pixel_delta_v = viewport_v / m_image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left =
        m_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    m_pixel00_loc = viewport_upper_left + 0.5 * (m_pixel_delta_u + m_pixel_delta_v);
}

Color Camera::rayColor(Ray r, const Hittable& world) const
{
    RaycastHit rec;
    if (world.hit(r, Interval(0, INFINITY), rec))
    {
        return (rec.m_normal + Color(1, 1, 1)) * 0.5f;
    }

    vec3 unit_direction = r.getDirection().unitVector();
    float a = (unit_direction.y() + 1.0f) * 0.5f;
    return Color(1.0f, 1.0f, 1.0f) * (1.0f - a) + Color(0.5f, 0.7f, 1.0f) * a;
}
