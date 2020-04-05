#pragma once
#include "Material.h"
class Dielectric : public Material
{
public:
	float refractiveIdx;

	Dielectric(float ri) : refractiveIdx(ri) {}

	virtual bool scatter(const Ray& rayIn, const hitRecord& record, vec3& attenuation, Ray& scattered) const;
};

