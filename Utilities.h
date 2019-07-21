#pragma once
#include "glm\vec3.hpp"
#include <glm/geometric.hpp>
#include <random>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const glm::vec3 RED(1, 0, 0);
const glm::vec3 GREEN(0, 1, 0);
const glm::vec3 BLUE(0, 0, 1);
const glm::vec3 WHITE(1, 1, 1);
const glm::vec3 BLACK(0, 0, 0);
const glm::vec3 LIGHTBLUE(0.5, 0.7, 1.0);

namespace mathStuff {

	static std::random_device randDevice;
	static std::mt19937 generator(randDevice());
	static std::uniform_real_distribution<float> distr(0, 1); //exclusive of 1

	glm::vec3 lerp(glm::vec3 start, glm::vec3 end, float howMuch);

	float squish(float t, float min, float max);

	glm::vec3 reflect(const glm::vec3& v, const glm::vec3 n);

	bool refract(const glm::vec3& v, const glm::vec3& n, float ni_over_nt, glm::vec3& refracted);

	// returns random number between 0 and 1 
	float getRand();

	// returns a random point in a unit sphere
	glm::vec3 randomInUnitSphere();

	//see https://en.wikipedia.org/wiki/Schlick%27s_approximation
	// fast computation for fresnel reflection
	float schick(float cosine, float refIdx);
	
}