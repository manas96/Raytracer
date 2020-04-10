#include "Bvh.h"
#include <algorithm>

BvhNode::BvhNode(std::vector<std::shared_ptr<Hitable>>& objects,
	size_t start, size_t end) {

	int axis = mathStuff::getRandInt(0, 2);
	auto comparator =	(axis == 0) ? boxXCompare
						: (axis == 1) ? boxYCompare
						: boxZCompare;

	size_t object_span = end - start;

    if (object_span == 1) {     // if just one element, assign it to both leaves
        left = right = objects[start];
    }
    else if (object_span == 2) {    
        if (comparator(objects[start], objects[start + 1])) {
            left = objects[start];
            right = objects[start + 1];
        }
        else {
            left = objects[start + 1];
            right = objects[start];
        }
    }
    else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span / 2;
        left = std::make_shared<BvhNode>(objects, start, mid);
        right = std::make_shared<BvhNode>(objects, mid, end);
    }

    Aabb box_left, box_right;

    if (!left->boundingBox(box_left) || !right->boundingBox(box_right))
        std::cout << "No bounding box in bvh_node constructor.\n";

    box = Aabb::surroundingBox(box_left, box_right);
}

bool BvhNode::boxCompare(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b, int axis) {
    Aabb boxA;
    Aabb boxB;

    if (!a->boundingBox(boxA) || !b->boundingBox(boxB))
        std::cout << "No bounding box in bvh_node constructor.\n";

    return boxA.min[axis] < boxB.min[axis];
}

bool BvhNode::boxXCompare(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b) {
    return BvhNode::boxCompare(a, b, 0);
}

bool BvhNode::boxYCompare(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b) {
    return BvhNode::boxCompare(a, b, 1);
}

bool BvhNode::boxZCompare(const std::shared_ptr<Hitable> a, const std::shared_ptr<Hitable> b) {
    return BvhNode::boxCompare(a, b, 2);
}
bool BvhNode::hit(const Ray& r, float tMin, float tMax, hitRecord& record) const {
	if (!box.hit(r, tMin, tMax)) return false;

	bool hitLeft = left->hit(r, tMin, tMax, record);
	bool hitRight = right->hit(r, tMin, hitLeft ? record.t : tMax, record); // tMax = closest hit point

	return hitLeft || hitRight;
}


bool BvhNode::boundingBox(Aabb& outputBox) const {
	outputBox = box;
	return true;
}