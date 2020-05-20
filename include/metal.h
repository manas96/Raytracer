#pragma once
#include <material.h>
#include <texture.h>

class Metal : public Material
{
public:		// TODO add texture to albedo
	std::shared_ptr<Texture> albedo;
	float fuzz;		// fuzziness, how much the reflection is blurred

	Metal(const std::shared_ptr<Texture> a, float fuzziness) : albedo(a), fuzz(fuzziness < 1 ? fuzziness : 1) {}

	virtual bool scatter(const Ray& rayIn, const hitRecord& record, rgb& attenuation, Ray& scattered) const;
};

