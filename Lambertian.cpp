#include "Lambertian.h"
 
bool Lambertian::scatter(const Ray& rayIn, const hitRecord& record, glm::vec3& attenuation, Ray& scattered) const {

	glm::vec3 target = record.p + record.normal + mathStuff::randomInUnitSphere();
	scattered = Ray(record.p, target - record.p);
	attenuation = albedo;
	return true;
}