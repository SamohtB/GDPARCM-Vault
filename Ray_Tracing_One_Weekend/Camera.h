#pragma once
#include "hittable.h"
#include "material.h"
#include "vector3.h"
#include "Utilities.h"
#include "RTImage.h"

class Camera {
public:
    Camera(
        float aspect_ratio = 1.0f,
        float image_width = 400.0f,
        int samples_per_pixel = 10,
        int max_depth = 10,
        float vfov = 90.f,
        vector3 look_from = vector3(0.f, 0.f, 0.f),
        vector3 look_at = vector3(0.f, 0.f, -1.f),
        vector3 vup = vector3(0.f, 1.f, 0.f),
        float defocus_angle = 0,
        float focus_dist = 10
    );

    Color rayColor(Ray r, int depth, const Hittable& world) const;
    Ray getRay(int i, int j);
    void render(const Hittable& world);

private:
    int   m_image_height;
    float m_pixel_sample_scale;
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


