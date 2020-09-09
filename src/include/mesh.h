#include <vec3aliases.h>
#include <hitable.h>
#include <vector>
#include <triangle.h>

class Mesh : public Hitable {
public:

	std::vector<point> vertices;		// TODO this is inefficient, add a VAO and VBO like mapping
	std::vector<Triangle> faces;

	Mesh() {}

	Mesh(std::vector<point> v, std::vector<Triangle> f) : vertices(v), faces(f) {}

	bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const override;

	bool boundingBox(Aabb& outputBox) const override;

};