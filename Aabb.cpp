#include "Aabb.h"

// Implements Andrew Kensler's(Pixar) AABB intersection algorithm
// source : http://psgraphics.blogspot.com/2016/02/new-simple-ray-box-test-from-andrew.html
 bool Aabb::hit(const Ray& r, float tMin, float tMax) const {
	using namespace mathStuff;
	for (int axis = 0; axis < 3; ++axis) {	// x,y,z axis
        float invD = 1.0f / r.direction()[axis];
        float t0 = (min[axis] - r.origin()[axis]) * invD;
        float t1 = (max[axis] - r.origin()[axis]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        tMin = t0 > tMin ? t0 : tMin;
        tMax = t1 < tMax ? t1 : tMax;
        if (tMax <= tMin)
            return false;
	}
	return true;
}

Aabb Aabb::surroundingBox(const Aabb box0, const Aabb box1) {
	using namespace mathStuff;
	vec3 surroundingMin(ffmin(box0.min.x, box1.min.x),
		ffmin(box0.min.y, box1.min.y),
		ffmin(box0.min.z, box1.min.z));
	vec3 surroundingMax(ffmax(box0.max.x, box1.max.x),
		ffmax(box0.max.y, box1.max.y),
		ffmax(box0.max.z, box1.max.z));
	return Aabb(surroundingMin, surroundingMax);
}