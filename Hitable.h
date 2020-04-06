#pragma once
#include "Ray.h"
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "Vec3aliases.h"
#include <memory>
// forward declaration 
class Material;

struct hitRecord {
	float t;		// the "t" parameter of a ray i.e. how far along the ray we are
	point p;		// point at which ray intersects geometry
	vec3 normal;
	bool frontFace;

	inline void setFaceNormal(const Ray& r, const vec3& outwardNormal) {
		frontFace = glm::dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
	std::shared_ptr<Material> materialPtr;
};

class Hitable {
public:
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const = 0;
};