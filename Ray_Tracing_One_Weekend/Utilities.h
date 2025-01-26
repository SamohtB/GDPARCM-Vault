#pragma once
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385f;

// Utility Functions

inline float degrees_to_radians(float degrees) 
{
    return degrees * pi / 180.0f;
}

inline float random_float() 
{
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline float random_float(float min, float max) 
{
    return min + (max - min) * random_float();
}

// Common Headers

#include "color.h"
#include "ray.h"
#include "vector3.h"
#include "Interval.h"