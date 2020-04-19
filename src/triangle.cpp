#include <triangle.h>

// an implementation of the Moller Trumbore algorithm from 
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
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
    if (u < 0.0f || u > 1.0f) return false; 
 
    vec3 qvec = cross(tvec, v0v1);
    float v = dot(r.direction(), qvec) * invDet;
    if (v < 0.0f || u + v > 1.0f) return false; 
 
    float t = dot(v0v2, qvec) * invDet;

    rec.t = t;
    rec.p = vec3(u,v,t);
    rec.materialPtr = material;
    rec.setFaceNormal(r, normalize(cross(v0v1, v0v2)));

    return true; 
}

// TODO verify
bool Triangle::boundingBox(Aabb& outputBox) const {
    using namespace mathStuff;
    vec3 offset(0.001f, 0.001f, 0.001f);
    point min(
                ffmin(v0.x, v1.x, v2.x),
                ffmin(v0.y, v1.y, v2.y),
                ffmin(v0.z, v1.z, v2.z));
    point max(
                ffmax(v0.x, v1.x, v2.x),
                ffmax(v0.y, v1.y, v2.y),
                ffmax(v0.z, v1.z, v2.z));
    outputBox = Aabb(min - offset, max + offset);
    return true;
}

