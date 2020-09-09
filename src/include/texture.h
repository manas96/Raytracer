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

class CheckerTexture : public Texture {
public:
	std::shared_ptr<Texture> odd;
	std::shared_ptr<Texture> even;

	CheckerTexture() {}
	CheckerTexture(std::shared_ptr<Texture> e, std::shared_ptr<Texture> o) : even(e), odd(o) {}

	virtual rgb value(float u, float v, const vec3& p) const {
		auto sines = sin(10.0f * p.x) * sin(10.0f * p.y) * sin(10.0f * p.z);
		return (sines < 0) ? odd->value(u, v, p) : even->value(u, v, p);
	}








};
