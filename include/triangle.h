#pragma once
#include <hitable.h>
#include <material.h>
#include <memory>

class Triangle : public Hitable 
{
public:
    point v0,v1,v2;
    std::shared_ptr<Material> material;
    vec3 normal;

    Triangle(point ver0, point ver1, point ver2, std::shared_ptr<Material> m): v0(ver0), v1(ver1), v2(ver2), material(m), normal(vec3(0,0,0))// TODO remove normal default value
     {}
    Triangle(point ver0, point ver1, point ver2, std::shared_ptr<Material> m, vec3 n) : v0(ver0), v1(ver1), v2(ver2), material(m), normal(n)
    {}

    bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const override;
    bool boundingBox(Aabb& outputBox) const override;
};