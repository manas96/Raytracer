#pragma once
#include "Hitable.h"
#include "Material.h"

class Sphere : public Hitable
{
public:
	glm::vec3 center;
	float radius;
	Material* material;

	Sphere(glm::vec3 c, float r, Material* m) : center(c), radius(r), material(m) {};
	
	//tMin and tMax are used to define valid range for calculations to avoid float inaccuracies.
	bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const override;
};

