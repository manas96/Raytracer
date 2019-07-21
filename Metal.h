#pragma once
#include "Material.h"

class Metal : public Material
{
public:
	glm::vec3 albedo;
	float fuzz;

	Metal(const glm::vec3& a, float fuzziness) : albedo(a) {
		if (fuzziness < 1) fuzz = fuzziness;
		else fuzz = 1;
	}

	virtual bool scatter(const Ray& rayIn, const hitRecord& record, glm::vec3& attenuation, Ray& scattered) const;
};

