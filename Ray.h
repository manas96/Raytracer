#pragma once
#include "glm/vec3.hpp"
#include "Vec3aliases.h"
class Ray
{
public:
	point orig;
	vec3 dir;

	Ray() {}
	Ray(const point o, const vec3 d) : orig(o), dir(d) {}
	point origin() const { return orig; }
	vec3 direction() const { return dir; }
	point pointAtParameter(float t) const { return orig + t * dir;  }

};

