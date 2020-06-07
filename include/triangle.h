#pragma once
#include <hitable.h>
#include <material.h>
#include <memory>

class Triangle : public Hitable 
{
public:
    point v0,v1,v2;     // Vertices of the triangle
    std::shared_ptr<Material> material;
    vec3 n0,n1,n2;      // Vertex normals of the triangle

    Triangle(point ver0, point ver1, point ver2, std::shared_ptr<Material> m): v0(ver0), v1(ver1), v2(ver2), material(m), n0(0,0,0), n1(0,0,0), n2(0,0,0)// TODO remove normal default value
     {}
    Triangle(point ver0, point ver1, point ver2, std::shared_ptr<Material> m, vec3 normal0, vec3 normal1, vec3 normal2) : v0(ver0), v1(ver1), v2(ver2), material(m), n0(normal0), n1(normal1), n2(normal2)
    {}

    bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const override;
    bool boundingBox(Aabb& outputBox) const override;
};