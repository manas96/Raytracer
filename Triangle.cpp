#include "Triangle.h"

// an implementation of the Moller Trumbore algorithm
bool Triangle::hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const {
    using namespace glm;
    // reference https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
    float kEpsilon = 0.001;
    vec3 v0v1 = v1 - v0; 
    vec3 v0v2 = v2 - v0; 
    // vec3 pvec = r.direction.crossProduct(v0v2); 
    vec3 pvec = cross(r.direction(), v0v2);
    // float det = v0v1.dotProduct(pvec); 
    float det = dot(v0v1, pvec);
    // // if the determinant is negative the triangle is backfacing
    // // if the determinant is close to 0, the ray misses the triangle
    if (det < kEpsilon) return false; 
    // // ray and triangle are parallel if det is close to 0
    if (fabs(det) < kEpsilon) return false; 

    float invDet = 1 / det; 
 
    vec3 tvec = r.origin() - v0; 
    // u = tvec.dotProduct(pvec) * invDet;
    float u = dot(tvec, pvec) * invDet; 
    if (u < 0 || u > 1) return false; 
 
    // Vec3f qvec = tvec.crossProduct(v0v1); 
    vec3 qvec = cross(tvec, v0v1);
    // v = dir.dotProduct(qvec) * invDet;
    float v = dot(r.direction(), qvec) * invDet;
    if (v < 0 || u + v > 1) return false; 
 
    // t = v0v2.dotProduct(qvec) * invDet; 
    float t = dot(v0v2, qvec) * invDet;

    rec.t = t;
    rec.p = vec3(u,v,t);
    rec.materialPtr = material;
    rec.normal = normalize(cross(v0v1, v0v2));

    return true; 
}