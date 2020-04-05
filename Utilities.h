#pragma once
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include <random>
#include "Vec3aliases.h"

constexpr float M_PI = 3.14159265358979323846f;

namespace color {
	extern rgb RED;
	extern rgb GREEN;
	extern rgb BLUE;
	extern rgb WHITE;
	extern rgb BLACK;
	extern rgb LIGHTBLUE;
}


namespace mathStuff {

	static std::random_device randDevice;
	static std::mt19937 generator(randDevice());
	static std::uniform_real_distribution<float> distr(0.0, 1.0); //exclusive of 1

	inline double degreesToRadians(float degrees) {
		return degrees * M_PI / 180;
	}

	inline float ffmin(float a, float b) { return a <= b ? a : b; }
	inline float ffmax(float a, float b) { return a >= b ? a : b; }

	vec3 lerp(vec3 start, vec3 end, float howMuch);

	float squish(float t, float min, float max);

	vec3 reflect(const vec3& v, const vec3 n);

	bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted);

	// returns random number between 0 and 1 
	float getRand();

	// returns a random point in a unit sphere
	point randomInUnitSphere();

	//see https://en.wikipedia.org/wiki/Schlick%27s_approximation
	// fast computation for fresnel reflection
	float schick(float cosine, float refIdx);
	
	// returns a random point in a unit disk
	point randomInUnitDisk();

}