#include "Utilities.h"

#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"

int main()
{
    HittableList world;
    Camera camera;

    auto material_ground = make_shared<Lambertian>(Color(0.8f, 0.8f, 0.0f));
    auto material_center = make_shared<Lambertian>(Color(0.1f, 0.2f, 0.5f));
    auto material_left = make_shared<Dielectric>(1.5f);
    auto material_bubble = make_shared<Dielectric>(1.f / 1.5f);
    auto material_right = make_shared<Metal>(Color(0.8f, 0.6f, 0.2f), 1.0f);

    world.add(make_shared<Sphere>(vector3(0.0f, -100.5f, -1.0f), 100.0f, material_ground));
    world.add(make_shared<Sphere>(vector3(0.0f, 0.0f, -1.2f), 0.5f, material_center));
    world.add(make_shared<Sphere>(vector3(-1.0f, 0.0f, -1.0f), 0.5f, material_left));
    world.add(make_shared<Sphere>(vector3(-1.0f, 0.0f, -1.0f), 0.4f, material_bubble));
    world.add(make_shared<Sphere>(vector3(1.0f, 0.0f, -1.0f), 0.5f, material_right));

    camera.m_aspect_ratio = 16.0f / 9.0f;
    camera.m_image_width = 400.0f;
    camera.m_samples_per_pixel = 100;
    camera.m_max_depth = 50;

    camera.render(world);
}