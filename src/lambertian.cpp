#include <lambertian.h>
 
bool Lambertian::scatter(const Ray& rayIn, const hitRecord& record, vec3& attenuation, Ray& scattered) const {

	vec3 scatterDirection = record.normal + mathStuff::randomUnitVector();
	scattered = Ray(record.p, scatterDirection);
	attenuation = albedo->value(record.u, record.v, record.p);
	return true;
}