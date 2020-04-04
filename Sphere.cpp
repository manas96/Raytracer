#include "Sphere.h"

bool Sphere::hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const{
	glm::vec3 oc = r.origin() - center;
	float a = glm::dot(r.direction(), r.direction());
	float b = glm::dot(oc, r.direction());
	float c = glm::dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(b * b - a * c)) / a;
		if (temp < tMax && temp > tMin) {
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;		// dividing cheaper than sqrt
			rec.materialPtr = material;
			return true;
		}
		temp = (-b + sqrt(b * b - a * c)) / a;
		if (temp < tMax && temp > tMin) {
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius; // can just use glm's normalize function
			rec.materialPtr = material;
			return true;
		}
	}
	return false;
}