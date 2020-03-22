#pragma once
#include "Ray.h"
#include "Hitable.h"
#include "glm/geometric.hpp"
#include "Utilities.h"

class Material {
public : 
	virtual bool scatter(const Ray& rayIn, const hitRecord& record, glm::vec3& attenuation, Ray& scattered) const = 0;
};