#pragma once
#include "Ray.h"
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "vec3aliases.h"
// forward declaration 
class Material;

struct hitRecord {
	float t;
	point p;		// point at which ray intersects geometry
	vec3 normal;
	bool frontFace;

	inline void setFaceNormal(const Ray& r, const vec3& outwardNormal) {
		frontFace = glm::dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
	Material* materialPtr;
};

class Hitable {
public:
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const = 0;
};