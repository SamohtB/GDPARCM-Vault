#include "Utilities.h"

#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"


Color rayColor(Ray r, const Hittable& world)
{
    RaycastHit rec;
    if (world.hit(r, Interval(0, infinity), rec)) 
    {
        return (rec.m_normal + Color(1, 1, 1)) * 0.5f;
    }

    vec3 unit_direction = r.getDirection().unitVector();
    float a = (unit_direction.y() + 1.0f) * 0.5f;
    return Color(1.0f, 1.0f, 1.0f) * (1.0f - a) + Color(0.5f, 0.7f, 1.0f) * a;
}

int main() 
{
    /* Image Properties */
    const float ASPECT_RATIO = 16.0f / 9.0f;
    const int IMAGE_WIDTH = 400;
    const int IMAGE_HEIGHT = 225;

    /* World Properties */
    HittableList world;

    world.add(make_shared<Sphere>(vector3(0.0f, 0.0f, -1.0f), 0.5f));
    world.add(make_shared<Sphere>(vector3(0.0f, -100.5f, -1.f), 100.f));

    /* Camera Properties */
    const float FOCAL_LENGTH = 1.0f;
    const float VIEWPORT_HEIGHT = 2.0f;
    const float VIEWPORT_WIDTH = VIEWPORT_HEIGHT * IMAGE_WIDTH / IMAGE_HEIGHT;
    const vector3 CAMERA_CENTER = vector3(0.0f, 0.0f, 0.0f);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vector3 viewport_u = vector3(VIEWPORT_WIDTH, 0.0f, 0.0f);
    vector3 viewport_v = vector3(0.0f, -VIEWPORT_HEIGHT, 0.0f);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vector3 pixel_delta_u = viewport_u / IMAGE_WIDTH;
    vector3 pixel_delta_v = viewport_v / IMAGE_HEIGHT;

    // Calculate the location of the upper left pixel.
    vector3 viewport_upper_left = CAMERA_CENTER - vec3(0, 0, FOCAL_LENGTH) - viewport_u / 2 - viewport_v / 2;
    vector3 pixel00_loc = viewport_upper_left + ((pixel_delta_u + pixel_delta_v) * 0.5f) ;

    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for (int j = 0; j < IMAGE_HEIGHT; j++) 
    {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - j) << ' ' << std::flush;

        for (int i = 0; i < IMAGE_WIDTH; i++) 
        {
            vector3 pixel_center = pixel00_loc + (pixel_delta_u * static_cast<float>(i)) + (pixel_delta_v * static_cast<float>(j));
            vector3 ray_direction = pixel_center - CAMERA_CENTER;
            Ray r(CAMERA_CENTER, ray_direction);

            Color pixel_color = rayColor(r, world);
            ColorUtils::Write_Color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}