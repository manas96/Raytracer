#include <utilities.h>

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

vec3 mathStuff::reflect(const vec3& incoming, const vec3 normal) {
	return incoming - 2.0f * glm::dot(incoming, normal) * normal;
}

float mathStuff::getRand() {
	static std::uniform_real_distribution<float> distr(0.0, 1.0); //exclusive of 1
	return distr(generator);
}

float mathStuff::getRand(float min, float max) {
	// TODO this is not efficient
	std::uniform_real_distribution<float> distr(min, max); // exclusive of max
	return distr(generator);
}

int mathStuff::getRandInt(int min, int max) {
	return static_cast<int>(getRand(min, max + 1));
}

vec3 mathStuff::randomInUnitDisk() {
	point p;
	do {
		p = 2.0f * vec3(getRand(), getRand(), 0) - vec3(1, 1, 0);
	} while (glm::dot(p, p) >= 1.0f);
	return p;
}

// TODO understand how this is better than randomInUnitSphere()?
//TODO optimize, this is slower than randomInUnitSphere()
vec3 mathStuff::randomUnitVector() {
	float a = getRand(0.0f, 2.0f * PI);
	float z = getRand(-1.0f, 1.0f);
	float r = sqrt(1 - z * z);
	return vec3(r * cos(a), r * sin(a), z);
}

point mathStuff::randomInUnitSphere() {
	while (true) {
		vec3 p = randomVec3(-1.0f, 1.0f);
		if (glm::dot(p, p) >= 1) continue;
		return p;
	}	
}

// see wikipedia for equation explanation
vec3 mathStuff::refract(const vec3& incoming, const vec3& normal, float etai_over_etat) {
	using namespace glm;
	float cosTheta = dot(-incoming, normal);
	vec3 refractedOutParallel = etai_over_etat * (incoming + cosTheta * normal);
	vec3 refractedOutPerpendicular = -sqrt(1.0f - dot(refractedOutParallel, refractedOutParallel)) * normal;
	return refractedOutParallel + refractedOutPerpendicular;
}

float mathStuff::schick(float cosine, float refIdx) {
	float r0 = (1 - refIdx) / (1 + refIdx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}






