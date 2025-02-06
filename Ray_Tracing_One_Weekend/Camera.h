#pragma once
#include "hittable.h"
#include "material.h"
#include "vector3.h"
#include "Utilities.h"
#include "RTImage.h"

class Camera {
public:
    Camera(
        int image_width = 400,
        int image_height = 400,
        int samples_per_pixel = 10,
        int max_depth = 10,
        float fov = 60.0f,
        float focus_distance = 0.f,
        float defocus_angle = 0.f,
        vec3 look_from = vec3(0.f, 0.f, -5.f),
        vec3 look_at = vec3(0.f, 0.f, 0.f),
        vec3 up = vec3(0.f, 1.f, 0.f)
    );

    Color rayColor(Ray r, int depth, const Hittable& world) const;
    Ray getRay(int i, int j);
    void render(const Hittable& world);

private:
    float m_defocus_angle;
    vector3  m_center;
    vector3  m_pixel00_loc;
    vector3  m_pixel_delta_u;
    vector3  m_pixel_delta_v;
    vector3  m_u, m_v, m_w;
    vector3  m_defocus_disk_u;
    vector3  m_defocus_disk_v;
    RTImage* m_output_image;

    vector3 sampleSquare() const;
    vector3 defocusDiskSample();
};


