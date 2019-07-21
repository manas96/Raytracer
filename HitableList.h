#pragma once
#include "Hitable.h"

// TODO change this to use std::vector
class HitableList :public Hitable
{
public :
	Hitable** list;
	int listSize;
	HitableList(Hitable** l, int n) { list = l; listSize = n; }
	bool hit(const Ray& r, float tMin, float tMax, hitRecord& record) const;
};

