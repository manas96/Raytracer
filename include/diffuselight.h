#include "material.h"
#include "texture.h"
#include "vec3aliases.h"

class DiffuseLight : public Material {
public:
	std::shared_ptr<Texture> emit;

	DiffuseLight(std::shared_ptr<Texture> e) : emit(e) {}

	virtual bool scatter(const Ray& r, const hitRecord& record, vec3& attenuation, Ray& scattered) const {
		return false;
	}

	virtual vec3 emitted(float u, float v, const vec3& p) const {
		return emit->value(u, v, p);
	}
};