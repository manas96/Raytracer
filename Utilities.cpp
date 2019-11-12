#include "Utilities.h"

glm::vec3 mathStuff::lerp(glm::vec3 start, glm::vec3 end, float howMuch) {
	return (1.0f - howMuch) * start + howMuch * end;
}

float mathStuff::squish(float t, float min, float max) {
	return (t - min) / (max - min);
}

glm::vec3 mathStuff::reflect(const glm::vec3& v, const glm::vec3 n) {
	return v - 2.0f * glm::dot(v, n) * n;
}

float mathStuff::getRand() {
	return distr(generator);
}

glm::vec3 mathStuff::randomInUnitDisk() {
	glm::vec3 p;
	do {
		p = 2.0f * glm::vec3(getRand(), getRand(), 0) - glm::vec3(1, 1, 0);
	} while (glm::dot(p, p) >= 1.0f);
	return p;
}

glm::vec3 mathStuff::randomInUnitSphere() {
	glm::vec3 p;
	do {
		p = 2.0f * glm::vec3(getRand(), getRand(), getRand()) - glm::vec3(1, 1, 1);
	} while (glm::length(p) >= 1.0f);
	return p;
}

// see wikipedia for equation explanation
bool mathStuff::refract(const glm::vec3& v, const glm::vec3& n, float ni_over_nt, glm::vec3& refracted) {
	glm::vec3 uv = glm::normalize(v);
	float dt = glm::dot(uv, n);
	float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant > 0) {
		refracted = ni_over_nt * (uv - n * dt) - n * (float)sqrt(discriminant);
		return true;
	}
	else
		return false;
}


float mathStuff::schick(float cosine, float refIdx) {
	float r0 = (1 - refIdx) / (1 + refIdx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}






