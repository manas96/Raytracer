#pragma once
#include <vec3aliases.h>
#include <ray.h>
#include <utilities.h>

class Aabb {
public:
	point min;		// we store two corners of the AABB : the one with minimum and maximum coordinates
	point max;

	Aabb() : min(point(0,0,0)), max(point(0,0,0)) {}

	Aabb(const point minimum, const point maximum) : min(minimum), max(maximum) {}

	bool hit(const Ray& r, float tMin, float tMax) const;

	static Aabb surroundingBox(const Aabb box0, const Aabb box1);

};
