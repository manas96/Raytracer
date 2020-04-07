#pragma once
#include "Vec3aliases.h"
#include "Ray.h"
#include "Utilities.h"

class Aabb {
public:
	point min;		// we store two corners of the AABB : the one with minimum and maximum coordinates
	point max;

	Aabb(const point minimum, const point maximum) : min(minimum), max(maximum) {}

	bool hit(const Ray& r, float tMin, float tMax) const;
};