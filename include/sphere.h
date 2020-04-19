#pragma once
#include <hitable.h>
#include <material.h>
#include <memory>

class Sphere : public Hitable
{
public:
	point center;
	float radius;
	std::shared_ptr<Material> material;

	Sphere(point c, float r, std::shared_ptr<Material> m) : center(c), radius(r), material(m) {};
	
	bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const override;
	bool boundingBox(Aabb& outputBox) const override;
};

