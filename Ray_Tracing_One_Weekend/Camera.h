#pragma once
#include "hittable.h"
#include "Utilities.h"

class Camera {
public:
    /* Public Camera Parameters Here */
    float m_aspect_ratio = 1.0f;
    float m_image_width = 400.0f;
    int   m_samples_per_pixel = 10;
    int   m_max_depth = 10;

    void render(const Hittable& world);

private:
    int   m_image_height;
    float m_pixel_sample_scale;
    vec3  m_center;
    vec3  m_pixel00_loc;
    vec3  m_pixel_delta_u;
    vec3  m_pixel_delta_v;


    void initialize();
    Color rayColor(Ray r, int depth, const Hittable& world) const;
    Ray getRay(int i, int j) const;
    vec3 sampleSquare() const;
};


