#pragma once
#include <ray.h>
#include <hitable.h>
#include <glm/geometric.hpp>
#include <utilities.h>
#include <vec3aliases.h>
#include <utilities.h>

class Material {
public : 
	virtual bool scatter(const Ray& rayIn, const hitRecord& record, rgb& attenuation, Ray& scattered) const = 0;

	virtual vec3 emitted(float u, float v, const vec3& p) const { return color::BLACK; }
};