#include "Utilities.h"

namespace color {
	rgb RED(1.0, 0.0, 0.0);
	rgb GREEN(0.0, 1.0, 0.0);
	rgb BLUE(0.0, 0.0, 1.0);
	rgb WHITE(1.0, 1.0, 1.0);
	rgb BLACK(0.0, 0.0, 0.0);
	rgb LIGHTBLUE(0.5, 0.7, 1.0);
}

namespace mathStuff {
	std::random_device randDevice;
	std::mt19937 generator(randDevice());
}


vec3 mathStuff::lerp(vec3 start, vec3 end, float howMuch) {
	return (1.0f - howMuch) * start + howMuch * end;
}

float mathStuff::squish(float t, float min, float max) {
	return (t - min) / (max - min);
}

vec3 mathStuff::reflect(const vec3& v, const vec3 n) {
	return v - 2.0f * glm::dot(v, n) * n;
}

float mathStuff::getRand() {
	static std::uniform_real_distribution<float> distr(0.0, 1.0); //exclusive of 1
	return distr(generator);
}

float mathStuff::getRand(float min, float max) {
	static std::uniform_real_distribution<float> distr(min, max); // exclusive of max
	return distr(generator);
}

vec3 mathStuff::randomInUnitDisk() {
	point p;
	do {
		p = 2.0f * vec3(getRand(), getRand(), 0) - vec3(1, 1, 0);
	} while (glm::dot(p, p) >= 1.0f);
	return p;
}

point mathStuff::randomInUnitSphere() {
	point p;
	do {
		p = 2.0f * vec3(getRand(), getRand(), getRand()) - vec3(1, 1, 1);
	} while (glm::length(p) >= 1.0f);
	return p;
}

// see wikipedia for equation explanation
bool mathStuff::refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
	vec3 uv = glm::normalize(v);
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






