#pragma once

#include <vec3aliases.h>

class Texture {
public:
	virtual rgb value(float u, float v, const vec3& p) const = 0;
};

class ConstantTexture : public Texture {
public:
	rgb color;

	ConstantTexture() {}
	ConstantTexture(const rgb colr) : color(colr) {}

	virtual rgb value(float u, float v, const vec3& p) const {
		return color;
	}
};