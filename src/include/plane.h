#pragma once
#include <hitable.h>
#include <memory>

class Plane : public Hitable
{
public:
	point p;		// Point on the plane
	vec3 n;			// Normal to the plane
	std::shared_ptr<Material> material;

	Plane(point point, vec3 normal): p(point), n(normal) {}

	bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const override;

	bool boundingBox(Aabb& outputBox) const override;

};