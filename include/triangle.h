#pragma once
#include <hitable.h>
#include <material.h>
#include <memory>

class Triangle : public Hitable 
{
    public:
    vec3 v0,v1,v2;
    std::shared_ptr<Material> material;

    Triangle(vec3 ver0, vec3 ver1, vec3 ver2, std::shared_ptr<Material> m): v0(ver0), v1(ver1), v2(ver2), material(m)
     {}

    bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const override;
    bool boundingBox(Aabb& outputBox) const override;
};