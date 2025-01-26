#include "Interval.h"

const Interval Interval::empty = Interval(INFINITY, -INFINITY);
const Interval Interval::universe = Interval(-INFINITY, INFINITY);

float Interval::size() const
{
	return max - min;
}

bool Interval::contains(float x) const
{
	return min <= x && x <= max;
}

bool Interval::surrounds(float x) const
{
	return min < x && x < max;
}