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
            Color pixel_color = Color(0.f, 0.f, 0.f);
            for (int sample = 0; sample < m_samples_per_pixel; sample++)
            {
                Ray r = getRay(i, j);
                pixel_color += rayColor(r, m_max_depth, world);
            }

            ColorUtils::writeColor(std::cout, pixel_color * m_pixel_sample_scale);
        }
    }

    std::clog << "\rDone.                 \n";
}

void Camera::initialize()
{
    m_image_height = int(m_image_width / m_aspect_ratio);
    m_image_height = (m_image_height < 1) ? 1 : m_image_height;

    m_pixel_sample_scale = 1.0f / (float)m_samples_per_pixel;

    m_center = m_look_from;

    // Determine viewport dimensions.
    float theta = degrees_to_radians(m_vfov);
    float h = std::tan(theta / 2.f);
    float viewport_height = 2.f * h * m_focus_dist;
    float viewport_width = viewport_height * (float(m_image_width) / m_image_height);

    m_w = (m_look_from - m_look_at).unitVector();
    m_u = m_vup.cross(m_w).unitVector();
    m_v = m_w.cross(m_u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = m_u * viewport_width;
    auto viewport_v = -m_v * viewport_height;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    m_pixel_delta_u = viewport_u / (float)m_image_width;
    m_pixel_delta_v = viewport_v / (float)m_image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left =
        m_center - (m_w * m_focus_dist) - viewport_u / 2 - viewport_v / 2;
    m_pixel00_loc = viewport_upper_left + (m_pixel_delta_u + m_pixel_delta_v) * 0.5f;

    // Calculate the camera defocus disk basis vectors.
    auto defocus_radius = m_focus_dist * std::tan(degrees_to_radians(m_defocus_angle / 2));
    m_defocus_disk_u = m_u * defocus_radius;
    m_defocus_disk_v = m_v * defocus_radius;
}

Color Camera::rayColor(Ray r, int depth, const Hittable& world) const
{
    if (depth <= 0)
    {
        return Color(0.f, 0.f, 0.f);
    }

    RaycastHit rec;
    if (world.hit(r, Interval(0.001f, INFINITY), rec))
    {
        Ray scattered;
        Color attenuation;

        if (rec.m_material->scatter(r, rec, attenuation, scattered))
        {
            return rayColor(scattered, depth - 1, world) * attenuation;
        }

        return Color(0.f, 0.f, 0.f);
    }

    vec3 unit_direction = r.getDirection().unitVector();
    float a = (unit_direction.y() + 1.0f) * 0.5f;
    return Color(1.0f, 1.0f, 1.0f) * (1.0f - a) + Color(0.5f, 0.7f, 1.0f) * a;
}

Ray Camera::getRay(int i, int j)
{
    auto offset = sampleSquare();
    auto pixel_sample = m_pixel00_loc
        +  (m_pixel_delta_u * (i + offset.x()))
        + (m_pixel_delta_v * (j + offset.y()));

    auto ray_origin = (m_defocus_angle <= 0) ? m_center : defocusDiskSample();
    auto ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}

vector3 Camera::sampleSquare() const 
{
    return vector3(random_float() - 0.5f, random_float() - 0.5f, 0.f);
}

vector3 Camera::defocusDiskSample()
{
    vector3 point = vector3::randomInUnitDisk();
    return m_center + (m_defocus_disk_u * point.x()) + (m_defocus_disk_v * point.y());
}
