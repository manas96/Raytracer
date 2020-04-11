#pragma once
#include <ray.h>
#include <hitable.h>
#include <glm/geometric.hpp>
#include <utilities.h>
#include <vec3aliases.h>

class Material {
public : 
	virtual bool scatter(const Ray& rayIn, const hitRecord& record, rgb& attenuation, Ray& scattered) const = 0;
};