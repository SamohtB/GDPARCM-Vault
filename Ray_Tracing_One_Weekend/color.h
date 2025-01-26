#pragma once
#include <iostream>
#include "vector3.h"
#include "Interval.h"

using Color = vector3;

class ColorUtils
{
public:
	static void writeColor(std::ostream& output, Color pixel_color)
	{
        float r = pixel_color.x();
        float g = pixel_color.y();
        float b = pixel_color.z();

        static const Interval intensity(0.000f, 0.999f);
        int rbyte = int(256 * intensity.clamp(r));
        int gbyte = int(256 * intensity.clamp(g));
        int bbyte = int(256 * intensity.clamp(b));

        output << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
	}
};
