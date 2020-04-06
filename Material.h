#pragma once
#include "Ray.h"
#include "Hitable.h"
#include "glm/geometric.hpp"
#include "Utilities.h"
#include "Vec3aliases.h"

class Material {
public : 
	virtual bool scatter(const Ray& rayIn, const hitRecord& record, rgb& attenuation, Ray& scattered) const = 0;
};