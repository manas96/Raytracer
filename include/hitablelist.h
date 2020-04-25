#pragma once
#include <hitable.h>
#include <aabb.h>
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
	void append(HitableList list) { objects.insert(objects.end(), list.objects.begin(), list.objects.end()); }

	bool hit(const Ray& r, float tMin, float tMax, hitRecord& record) const;

	bool boundingBox(Aabb& outputBox) const override;
};

