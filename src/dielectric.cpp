#include <dielectric.h>

// Using a negative radius makes the normals point inwards, resulting in a transparent surface

bool Dielectric::scatter(const Ray& rayIn, const hitRecord& record, rgb& attenuation, Ray& scattered) const {
	
	attenuation = rgb(1.0f, 1.0f, 1.0f);	// perfect dielectric, absorbs no wavelength
	float etai_over_etat = (record.frontFace) ? (1.0f / refractiveIdx) : (refractiveIdx);
	
	vec3 unitDirection = glm::normalize(rayIn.direction());
	float cosTheta = mathStuff::ffmin(glm::dot(-unitDirection, record.normal), 1.0f);
	double sinTheta = sqrt(1.0f - cosTheta * cosTheta);
	
	if (etai_over_etat * sinTheta > 1.0f) { // if total internal reflection happens
		vec3 reflected = mathStuff::reflect(unitDirection, record.normal);
		scattered = Ray(record.p, reflected);
		return true;
	}
	double reflect_probability = mathStuff::schick(cosTheta, etai_over_etat);
	if (mathStuff::getRand() < reflect_probability) { // TODO combine this with earlier condition
		vec3 reflected = mathStuff::reflect(unitDirection, record.normal);
		scattered = Ray(record.p, reflected);
		return true;
	}
	vec3 refracted = mathStuff::refract(unitDirection, record.normal, etai_over_etat);
	scattered = Ray(record.p, refracted);
	return true;
}