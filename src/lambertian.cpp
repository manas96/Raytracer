#include <lambertian.h>
 
bool Lambertian::scatter(const Ray& rayIn, const hitRecord& record, vec3& attenuation, Ray& scattered) const {

	vec3 target = record.p + record.normal + mathStuff::randomInUnitSphere();
	// vec3 target = record.p + record.normal + mathStuff::randomUnitVector();
	scattered = Ray(record.p, target - record.p);
	attenuation = albedo;
	return true;
}