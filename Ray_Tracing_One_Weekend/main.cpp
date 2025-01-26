#include "Utilities.h"

#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"

int main()
{
    HittableList world;
    Camera camera;

    world.add(make_shared<Sphere>(vector3(0.0f, 0.0f, -1.0f), 0.5f));
    world.add(make_shared<Sphere>(vector3(0.0f, -100.5f, -1.f), 100.f));

    camera.m_aspect_ratio = 16.0f / 9.0f;
    camera.m_image_width = 400.0f;
    camera.m_samples_per_pixel = 100;
    camera.m_max_depth = 50;

    camera.render(world);
}