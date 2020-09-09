#pragma once
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <random>
#include <vec3aliases.h>

constexpr float PI = 3.14159265358979323846f;

namespace color {
	extern rgb RED;
	extern rgb GREEN;
	extern rgb BLUE;
	extern rgb WHITE;
	extern rgb BLACK;
	extern rgb YELLOW;
	extern rgb LIGHTBLUE;
}



namespace mathStuff {

	extern std::random_device randDevice;
	extern std::mt19937 generator;

	inline double degreesToRadians(float degrees) {
		return degrees * PI / 180;
	}

	inline float ffmin(float a, float b) { return a <= b ? a : b; }
	inline float ffmin(float a, float b, float c) { return ffmin(ffmin(a, b), c); }

	inline float ffmax(float a, float b) { return a >= b ? a : b; }
	inline float ffmax(float a, float b, float c) { return ffmax(ffmax(a, b), c); }

	// clamps x to [min,max]
	inline float clamp(float x, float min, float max) {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

	vec3 lerp(vec3 start, vec3 end, float howMuch);

	float squish(float t, float min, float max);

	vec3 reflect(const vec3& incoming, const vec3 normal);

	vec3 refract(const vec3& incoming, const vec3& normal, float etai_over_etat);

	// returns random number between [0,1)
	float getRand();

	// returns random number between [min,max)
	float getRand(float min, float max);

	// returns random integer in [min,max]
	int getRandInt(int min, int max);

	inline vec3 randomVec3() { return vec3(getRand(), getRand(), getRand()); }
	inline vec3 randomVec3(float min, float max) { return vec3(getRand(min, max), getRand(min, max), getRand(min, max)); }

	// returns a random point in a unit sphere
	point randomInUnitSphere();

	point randomInHemisphere(const vec3& normal);

	vec3 randomUnitVector();

	//see https://en.wikipedia.org/wiki/Schlick%27s_approximation
	// fast computation for fresnel reflection
	float schick(float cosine, float refIdx);
	
	// returns a random point in a unit disk
	point randomInUnitDisk();

}