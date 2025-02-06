#include "Utilities.h"

#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "RayTraceThread.h"

int main()
{
    HittableList world;
    
    auto ground_material = make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f));
    world.add(make_shared<Sphere>(vector3(0.f, -1000.f, 0.f), 1000.f, ground_material));

    int num_spheres = 100;

    for (int i = 0; i < num_spheres; i++)
    {
        auto choose_mat = RANDOM_FLOAT();
        vector3 center = vector3(RANDOM_FLOAT(-5.f, 5.f), 0.2f, RANDOM_FLOAT(-5.f, 5.f));

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

            else if (choose_mat < 0.95)
            {
                // metal
                auto albedo = Color::random(0.5f, 1.f);
                auto fuzz = RANDOM_FLOAT(0.f, 0.5f);
                sphere_material = make_shared<Metal>(albedo, fuzz);
                world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
            }

            else
            {
                // glass
                sphere_material = make_shared<Dielectric>(1.5f);
                world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5f);
    world.add(make_shared<Sphere>(vector3(0.f, 1.f, 4.f), 1.0f, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
    world.add(make_shared<Sphere>(vector3(-4.f, 1.f, 0.f), 1.0f, material2));

    auto material3 = make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
    world.add(make_shared<Sphere>(vector3(5.f, 1.f, 0.f), 1.0f, material3));

    auto material4 = make_shared<Metal>(Color(0.8f, 0.2f, 0.1f), 0.0f);
    world.add(make_shared<Sphere>(vector3(4.f, 1.f, -4.f), 1.0f, material4));

    float aspect_ratio = 1.f;
    int image_width = 512;
    int samples_per_pixel = 100;
    int image_height = static_cast<int> (image_width / aspect_ratio);
    int depth = 30;

    /* camera properties */
    Camera camera(image_width, image_height, samples_per_pixel, depth,
        60.0f,                  // fov
        10.0f,                  // focus distance
        0.6f,                   // defocus angle
        vector3(13, 2, 3),      //look from
        vector3(0.f, 0.f, 0.f), //look at
        vector3(0.f, 1.f, 0.f)  //vup 
    );

    std::vector<RayTraceThread*> thread_list;
    int core_count = 24;
    int lines_per_core = image_height / core_count;
    
    int image_height_start = 0;
    int image_height_end = lines_per_core;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    /* Thread Start */
    for (int i = 0; i < core_count; i++)
    {
        /* give remaining scanlines to last thread */
        if (i == core_count - 1)
        {
            image_height_end = image_height;
        }

        RayTraceThread* thread = new RayTraceThread(world, &camera, image_height_start, 
            image_height_end, image_width, samples_per_pixel, depth);
        thread->start();
        thread_list.push_back(thread);

        image_height_start += lines_per_core;
        image_height_end += lines_per_core;
    }

    /* Primitive Thread Sync */
    bool is_scanning = true;

    while (is_scanning)
    {
        for (int i = 0; i < thread_list.size(); i++)
        {
            is_scanning = false;
            if (thread_list[i]->isRunning())
            {
                is_scanning = true;
                break;
            }
        }

        IETThread::sleep(100);
    }

    /* Compile Image Data to ensure single access to output */
    cv::Mat image_container = cv::Mat::zeros(image_height, image_width, CV_8UC3);

    for (int i = 0; i < thread_list.size(); i++)
    {
        cv::Mat thread_image = thread_list[i]->getImageData();

        int row_start = thread_list[i]->getRowStart();
        int row_end = thread_list[i]->getRowEnd();

        /* union of matrices */
        cv::bitwise_or(thread_image, image_container, image_container);
    }

    cv::String file_name = "_Image_Render.png";
    cv::imwrite(file_name, image_container);

}