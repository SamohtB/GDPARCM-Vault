#pragma once
#include "hittable.h"
#include "color.h"

class Camera {
public:
    /* Public Camera Parameters Here */
    float m_aspect_ratio = 1.0f;
    float m_image_width = 400.0f;

    void render(const Hittable& world);

private:
    int   m_image_height;
    vec3  m_center;
    vec3  m_pixel00_loc;
    vec3  m_pixel_delta_u;
    vec3  m_pixel_delta_v;


    void initialize();
    Color rayColor(Ray r, const Hittable& world) const;
};


