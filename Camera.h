#pragma once
#include "Utilities.h"
#include "Ray.h"


class Camera {
public: 
	glm::vec3 origin;
	glm::vec3 lowerLeftCorner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
	float lensRadius;
	glm::vec3 u, v, w;

			//verticalFOV is in degrees
	Camera(glm::vec3 lookFrom, glm::vec3 lookAt, glm::vec3 vUp, float  verticalFov, float aspectRatio, float apeture, float focusDist);

	Ray getRay(float s, float t);

};