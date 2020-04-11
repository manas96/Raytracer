#pragma once
#include <material.h>

class Lambertian : public Material
{
public:
	vec3 albedo;

	Lambertian(const vec3& a) : albedo(a) {}
	virtual bool scatter(const Ray& rayIn, const hitRecord& record, vec3& attenuation, Ray& scattered) const override;
};

