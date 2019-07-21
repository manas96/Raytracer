#include "Camera.h"

Camera::Camera(glm::vec3 lookFrom, glm::vec3 lookAt, glm::vec3 vUp, float  verticalFov, float aspectRatio) {
	glm::vec3 u, v, w;
	float theta = verticalFov * M_PI / 180.0f;
	float halfHeight = tan(theta / 2);
	float halfWidth = aspectRatio * halfHeight;
	origin = lookFrom;
	w = glm::normalize(lookFrom - lookAt);
	u = glm::normalize(glm::cross(vUp, w));
	v = glm::cross(w, u);
	lowerLeftCorner = glm::vec3(-halfWidth, -halfHeight, -1.0);
	lowerLeftCorner = origin - halfWidth * u - halfHeight * v - w;
	horizontal = 2 * halfWidth * u;
	vertical = 2 * halfHeight * v;
}

Ray Camera::getRay(float s, float t) {
	return Ray(origin, lowerLeftCorner + s * horizontal + t * vertical - origin);
}