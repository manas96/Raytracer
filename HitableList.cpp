#include "HitableList.h"

bool HitableList::hit(const Ray& r, float tMin, float tMax, hitRecord& record) const {
	hitRecord tempRecord;
	bool hitAnything = false;
	float closestSoFar = tMax;

	for (const auto& object : objects) {
		if (object->hit(r, tMin, closestSoFar, tempRecord)) {
			hitAnything = true;
			closestSoFar = tempRecord.t;
			record = tempRecord;
		}
	}
	return hitAnything;
}

bool HitableList::boundingBox(Aabb& outputBox) const {
	if (objects.empty()) return false;

	Aabb tempBox;
	bool firstTrue = objects[0]->boundingBox(tempBox);
	if (!firstTrue) return false;

	outputBox = tempBox;
	for (const auto& object : objects) {
		if (!object->boundingBox(tempBox)) return false;
		outputBox = Aabb::surroundingBox(outputBox, tempBox);
	}
	return true;
}

