#pragma once
#include "hittable.h"
#include "material.h"
#include "vector3.h"
#include "Utilities.h"
#include "RTImage.h"

class Camera {
public:
    /* Public Camera Parameters Here */
    float m_aspect_ratio = 1.0f;
    float m_image_width = 400.0f;
    int   m_samples_per_pixel = 10;
    int   m_max_depth = 10;

    float m_vfov = 90.f;
    vector3  m_look_from = vector3(0.f, 0.f, 0.f);     // Point camera is looking from
    vector3  m_look_at = vector3(0.f, 0.f, -1.f);      // Point camera is looking at
    vector3  m_vup = vec3(0.f, 1.f, 0.f);              // Camera-relative "up" direction

    float m_defocus_angle = 0;
    float m_focus_dist = 10;

    void render(const Hittable& world);

private:
    int   m_image_height;
    float m_pixel_sample_scale;
    vector3  m_center;
    vector3  m_pixel00_loc;
    vector3  m_pixel_delta_u;
    vector3  m_pixel_delta_v;
    vector3  m_u, m_v, m_w;
    vector3  m_defocus_disk_u;
    vector3  m_defocus_disk_v;
    RTImage* m_output_image;

    void initialize();
    Color rayColor(Ray r, int depth, const Hittable& world) const;
    Ray getRay(int i, int j);
    vector3 sampleSquare() const;
    vector3 defocusDiskSample();
};


