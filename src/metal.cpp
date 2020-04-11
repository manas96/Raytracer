#include <metal.h>

bool Metal::scatter(const Ray& rayIn, const hitRecord& record, rgb& attenuation, Ray& scattered) const {
	vec3 reflected = mathStuff::reflect(glm::normalize(rayIn.direction()), record.normal);
	scattered = Ray(record.p, reflected + fuzz * mathStuff::randomInUnitSphere());
	attenuation = albedo;
	return glm::dot(scattered.direction(), record.normal) > 0;
}