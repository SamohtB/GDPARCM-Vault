#pragma once
#include <iostream>
#include "vector3.h"

using Color = vector3;

class ColorUtils
{
public:
	static void writeColor(std::ostream& output, Color& pixel_color)
	{
        float r = pixel_color.x();
        float g = pixel_color.y();
        float b = pixel_color.z();

        int rbyte = static_cast<int>(255.999 * r);
        int gbyte = static_cast<int>(255.999 * g);
        int bbyte = static_cast<int>(255.999 * b);

        output << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
	}
};
