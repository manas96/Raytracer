#pragma once
#include "glm/vec3.hpp"
#include "vec3aliases.h"
class Ray
{
public:
	point orig;
	glm::vec3 dir;

	Ray() {}
	Ray(const point o, const glm::vec3 d) : orig(o), dir(d) {}
	point origin() const { return orig; }
	glm::vec3 direction() const { return dir; }
	point pointAtParameter(float t) const { return orig + t * dir;  }

};

