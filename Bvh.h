#pragma once
#include "Vec3aliases.h"
#include "Hitable.h"
#include "Vec3aliases.h"
#include "HitableList.h"
#include "Ray.h"
#include "Aabb.h"
#include <iostream>


class BvhNode : public Hitable {
public:
	std::shared_ptr<Hitable> left;
	std::shared_ptr<Hitable> right;
	Aabb box;

	BvhNode() {}

	BvhNode(HitableList& list) : BvhNode(list.objects, 0, list.objects.size()) {}
	
	BvhNode(std::vector<std::shared_ptr<Hitable>>& objects,
			size_t start, size_t end);

	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& record) const override;

	virtual bool boundingBox(Aabb& outputBox) const override;
private:
	static bool boxCompare(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b, int axis);
	static bool boxXCompare(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b);
	static bool boxYCompare(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b);
	static bool boxZCompare(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b);
};
