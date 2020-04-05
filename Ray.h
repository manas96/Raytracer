#pragma once
#include "glm/vec3.hpp"
#include "vec3aliases.h"
class Ray
{
public:
	point origin;
	glm::vec3 direction;

	Ray() {}
	Ray(const point orig, const glm::vec3 dir) : origin(orig), direction(dir) {}
	glm::vec3 origin() const { return origin; }
	glm::vec3 direction() const { return direction; }
	point pointAtParameter(float t) const { return origin + t * direction;  }

};

