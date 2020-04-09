#pragma once
#include "Vec3aliases.h"
#include "Ray.h"
#include "Utilities.h"

class Aabb {
public:
	point min;		// we store two corners of the AABB : the one with minimum and maximum coordinates
	point max;

	Aabb() {}
	Aabb(const point minimum, const point maximum) : min(minimum), max(maximum) {}

	bool hit(const Ray& r, float tMin, float tMax) const;
};

Aabb surroundingBox(const Aabb box0, const Aabb box1) {
	using namespace mathStuff;
	vec3 surroundingMin(	ffmin(box0.min.x, box1.min.x),
							ffmin(box0.min.y, box1.min.y),
							ffmin(box0.min.z, box1.min.z));
	vec3 surroundingMax(	ffmax(box0.max.x, box1.max.x),
							ffmax(box0.max.y, box1.max.y),
							ffmax(box0.max.z, box1.max.z));
	return Aabb(surroundingMin, surroundingMax);
}