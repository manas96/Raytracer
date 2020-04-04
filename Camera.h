#pragma once
#include "Utilities.h"
#include "Ray.h"
#include "vec3aliases.h"

class Camera {
public: 
	point origin;
	point lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
	float lensRadius;
	vec3 u, v, w;

			//verticalFOV is in degrees
	Camera(point lookFrom, point lookAt, vec3 vUp, float  verticalFov, float aspectRatio, float apeture, float focusDist);

	Ray getRay(float s, float t);

};