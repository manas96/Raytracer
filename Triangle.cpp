#include "Triangle.h"

// an implementation of the Moller Trumbore algorithm from 
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
// TODO verify with wikipedia algorithm, some blurring occurs around one triangle vertex
bool Triangle::hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const {
    using namespace glm;
    
    vec3 v0v1 = v1 - v0; 
    vec3 v0v2 = v2 - v0; 
    vec3 pvec = cross(r.direction(), v0v2);
    float det = dot(v0v1, pvec);
    // // if the determinant is negative the triangle is backfacing
    // // if the determinant is close to 0, the ray misses the triangle
    if (det < tMin) return false; 
    // // ray and triangle are parallel if det is close to 0
    if (fabs(det) < tMin) return false; 

    float invDet = 1 / det; 
    vec3 tvec = r.origin() - v0; 
    float u = dot(tvec, pvec) * invDet; 
    if (u < 0 || u > 1) return false; 
 
    vec3 qvec = cross(tvec, v0v1);
    float v = dot(r.direction(), qvec) * invDet;
    if (v < 0 || u + v > 1) return false; 
 
    float t = dot(v0v2, qvec) * invDet;

    rec.t = t;
    rec.p = vec3(u,v,t);
    rec.materialPtr = material;
    rec.normal = normalize(cross(v0v1, v0v2));      // TODO use setFaceNormal()

    return true; 
}