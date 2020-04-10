#pragma once
#include "Hitable.h"
#include "Aabb.h"
#include <memory>
#include <vector>

class HitableList :public Hitable
{
public :
	std::vector<std::shared_ptr<Hitable>> objects;

	HitableList() {}
	HitableList(std::shared_ptr<Hitable> object) { add(object); }

	void clear() { objects.clear(); }
	void add(std::shared_ptr<Hitable> object) { objects.push_back(object); }

	bool hit(const Ray& r, float tMin, float tMax, hitRecord& record) const;

	bool boundingBox(Aabb& outputBox) const override;
};

