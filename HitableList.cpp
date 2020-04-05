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
