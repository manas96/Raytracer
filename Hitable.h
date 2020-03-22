#pragma once
#include "Ray.h"
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
// forward declaration 
class Material;

struct hitRecord {
	float t;
	glm::vec3 p;
	glm::vec3 normal;
	Material* materialPtr;
};

class Hitable {
public:
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const = 0;
};