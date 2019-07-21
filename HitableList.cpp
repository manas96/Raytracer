#include "HitableList.h"

bool HitableList::hit(const Ray& r, float tMin, float tMax, hitRecord& record) const {
	hitRecord tempRecord;
	bool hitAnything = false;
	double closestSoFar = tMax;
	for (int i = 0; i < listSize; i++) {
		if (list[i]->hit(r, tMin, closestSoFar, tempRecord)) {
			hitAnything = true;
			closestSoFar = tempRecord.t;
			record = tempRecord;
		}
	}
	return hitAnything;
}
