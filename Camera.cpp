#include "Camera.h"

Camera::Camera(point lookFrom, point lookAt, vec3 vUp, float  verticalFov, float aspectRatio, float apeture, float focusDist) {
	lensRadius = apeture / 2;
	float theta = verticalFov * PI / 180.0f;
	float halfHeight = tan(theta / 2);
	float halfWidth = aspectRatio * halfHeight;
	origin = lookFrom;
	w = glm::normalize(lookFrom - lookAt);
	u = glm::normalize(glm::cross(vUp, w));
	v = glm::cross(w, u);
	lowerLeftCorner = vec3(-halfWidth, -halfHeight, 
-1.0);
	lowerLeftCorner = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
	horizontal = 2 * halfWidth * focusDist * u;
	vertical = 2 * halfHeight * focusDist * v;
}

Ray Camera::getRay(float s, float t) {
	vec3 rd = lensRadius * mathStuff::randomInUnitDisk();
	vec3 offset = u * rd.x + v * rd.y;
	return Ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
}