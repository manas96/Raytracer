#include "Dielectric.h"

// Using a negative radius makes the normals point inwards, resulting in a transparent surface

bool Dielectric::scatter(const Ray& rayIn, const hitRecord& record, glm::vec3& attenuation, Ray& scattered) const {
	glm::vec3 outwardNormal;
	glm::vec3 reflected = mathStuff::reflect(rayIn.direction(), record.normal);
	float ni_over_nt;
	attenuation = glm::vec3(1, 1, 1);		
	glm::vec3 refracted;
	float reflectProb;
	float cosine;

	if (glm::dot(rayIn.direction(), record.normal) > 0) { //if incoming ray is not parallel to the surface of incidence / if not total internal reflection
		outwardNormal = -record.normal;
		ni_over_nt = refractiveIdx;
		cosine = refractiveIdx * glm::dot(rayIn.direction(), record.normal) / glm::length(rayIn.direction());
	}
	else {
		outwardNormal = record.normal;
		ni_over_nt = 1.0f / refractiveIdx;
		cosine = -glm::dot(rayIn.direction(), record.normal) / glm::length(rayIn.direction());
	}
	if (mathStuff::refract(rayIn.direction(), outwardNormal, ni_over_nt, refracted)) {
		reflectProb = mathStuff::schick(cosine, refractiveIdx);
	}
	else {
		reflectProb = 1.0f;
	}
	if (mathStuff::getRand() < reflectProb) {
		scattered = Ray(record.p, reflected);
	}
	else {
		scattered = Ray(record.p, refracted);
	}
	return true;
}