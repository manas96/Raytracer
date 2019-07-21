#pragma once
#include "Ray.h"
#include <glm/>

class camera {
public:
	glm::vec3 origin;
	glm::vec3 lowerLeftCorner;
	glm::vec3 horizontal;
	glm::vec3 vertical;

	camera() {

	}
};