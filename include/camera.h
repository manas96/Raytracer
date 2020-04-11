#pragma once
#include <utilities.h>
#include <ray.h>
#include <vec3aliases.h>

class Camera {
public: 
	point origin;
	point lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
	float lensRadius;
	vec3 u, v, w;	// orthonormal basis to fully describe camera position

			//verticalFOV is in degrees
	Camera(point lookFrom, point lookAt, vec3 vUp, float  verticalFov, float aspectRatio, float apeture, float focusDist);

	Ray getRay(float s, float t);

};