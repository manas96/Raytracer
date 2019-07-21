#pragma once
#include "Material.h"

class Lambertian : public Material
{
public:
	glm::vec3 albedo;

	Lambertian(const glm::vec3& a) : albedo(a) {}
	virtual bool scatter(const Ray& rayIn, const hitRecord& record, glm::vec3& attenuation, Ray& scattered) const override;
};

