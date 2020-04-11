#pragma once
#include <material.h>

class Metal : public Material
{
public:
	rgb albedo;
	float fuzz;		// fuzziness, how much the reflection is blurred

	Metal(const vec3& a, float fuzziness) : albedo(a), fuzz(fuzziness < 1 ? fuzziness : 1) {}

	virtual bool scatter(const Ray& rayIn, const hitRecord& record, rgb& attenuation, Ray& scattered) const;
};

