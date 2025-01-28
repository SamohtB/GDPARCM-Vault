#include "Utilities.h"

#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"

int main()
{
    HittableList world;
    
    auto ground_material = make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f));
    world.add(make_shared<Sphere>(vector3(0.f, -1000.f, 0.f), 1000.f, ground_material));

    for (int a = -11; a < 11; a++) 
    {
        for (int b = -11; b < 11; b++) 
        {
            auto choose_mat = RANDOM_FLOAT();
            vector3 center(a + 0.9f * RANDOM_FLOAT(), 0.2f, b + 0.9f * RANDOM_FLOAT());

            if ((center - vector3(4.f, 0.2f, 0.f)).length() > 0.9f) 
            {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) 
                {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5f, 1.f);
                    auto fuzz = RANDOM_FLOAT(0.f, 0.5f);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5f);
                    world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5f);
    world.add(make_shared<Sphere>(vector3(0.f, 1.f, 0.f), 1.0f, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
    world.add(make_shared<Sphere>(vector3(-4.f, 1.f, 0.f), 1.0f, material2));

    auto material3 = make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
    world.add(make_shared<Sphere>(vector3(4.f, 1.f, 0.f), 1.0f, material3));

    Camera camera;

    camera.m_aspect_ratio = 1.f;
    camera.m_image_width = 512.f;
    camera.m_samples_per_pixel = 200;
    camera.m_max_depth = 50;

    camera.m_vfov = 20.0f;
    camera.m_look_from = vector3(13, 2, 3);
    camera.m_look_at = vector3(0, 0, 0);
    camera.m_vup = vec3(0, 1, 0);

    camera.m_defocus_angle = 0.6f;
    camera.m_focus_dist = 10.0f;

    camera.render(world);
}