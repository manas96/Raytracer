#pragma once
#include <material.h>

class Dielectric : public Material
{
public:
	float refractiveIdx;

	Dielectric(float ri) : refractiveIdx(ri) {}

	virtual bool scatter(const Ray& rayIn, const hitRecord& record, rgb& attenuation, Ray& scattered) const;
};

