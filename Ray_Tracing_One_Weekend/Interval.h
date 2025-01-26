#pragma once
#include <math.h>

class Interval 
{
public:
    float min, max;

    Interval() : min(INFINITY), max(-INFINITY) {}

    Interval(float min, float max) : min(min), max(max) {}

    float size() const;
    bool contains(float x) const;
    bool surrounds(float x) const;

    static const Interval empty;
    static const Interval universe;
};
