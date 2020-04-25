#include <mesh.h>

bool Mesh::hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const {
	return false;
}

bool Mesh::boundingBox(Aabb& outputBox) const {
	return false;
}
