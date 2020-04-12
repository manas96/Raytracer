#pragma once
#include <material.h>
#include <texture.h>

class Lambertian : public Material
{
public:
	std::shared_ptr<Texture> albedo;

	Lambertian(const std::shared_ptr<Texture> a) : albedo(a) {}
	virtual bool scatter(const Ray& rayIn, const hitRecord& record, vec3& attenuation, Ray& scattered) const override;
};

