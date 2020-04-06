#pragma once
#include "Hitable.h"
#include "Material.h"
#include <memory>

class Sphere : public Hitable
{
public:
	vec3 center;
	float radius;
	std::shared_ptr<Material> material;

	Sphere(vec3 c, float r, std::shared_ptr<Material> m) : center(c), radius(r), material(m) {};
	
	//tMin and tMax are used to define valid range for calculations to avoid float inaccuracies.
	bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const override;
};

