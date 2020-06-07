#include <hitablelist.h>
#include <sphere.h>
#include <triangle.h>
#include <metal.h>
#include <lambertian.h>
#include <dielectric.h>
#include <utilities.h>
#include <vector>
#include <iostream>
#include <glm/gtx/transform.hpp>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace scenes {

	static HitableList scene;
	using std::make_shared;

	HitableList exampleScene() {
		scene.clear();
		std::shared_ptr<DiffuseLight> whiteLight = make_shared<DiffuseLight>(make_shared<ConstantTexture>(rgb(10.0f, 10.0f, 10.0f)));

		auto checker = make_shared<CheckerTexture>(make_shared<ConstantTexture>(rgb(0.2, 0.3, 0.1)), make_shared<ConstantTexture>(rgb(0.9, 0.9, 0.9)));

		scene.add(make_shared<Sphere>(point(0.0f, -100.5f, -1.0f), 100.0f, make_shared<Lambertian>(checker)));		// ground sphere

		scene.add(make_shared<Sphere>(point(1.0f, 0.0f, -1.0f), 0.5f, make_shared<Metal>(make_shared<ConstantTexture>(rgb(0.2f, 0.8f, 0.2f)), 0.0f)));

		scene.add(make_shared<Sphere>(point(-2.0f, 1.0f, 1.0f), 1.0f,
			//whiteLight));
		make_shared<Metal>(make_shared<ConstantTexture>(rgb(1.0f, 0.2f, 0.7f)), 0.0f)));

		scene.add(make_shared<Sphere>(point(-1.0f, 0.0f, -1.0f), 0.5f, make_shared<Dielectric>(1.5f)));

		scene.add(make_shared<Sphere>(point(-1.0f, 0.0f, -1.0f), -0.45f,
			//whiteLight));
			make_shared<Dielectric>(1.5f)));

		//scene.add(make_shared<Sphere>(point(0.0f, .0f, -1.0f), -0.5f, make_shared<Dielectric>(1.7f)));

		scene.add(make_shared<Triangle>(point(-2.0f + 1, 1.0f, -1.0f), point(0.0f + 1, 2.0f, -1.0f), point(0.0f + 1, 3.0f, -1.0f),
			make_shared<Metal>(make_shared<ConstantTexture>(rgb(1.0f, 0.2f, 0.7f)), 0.0f)));

		scene.add(make_shared<Triangle>(point(0.0f, 1.0f, -1.0f), point(2.0f, 2.0f, -1.0f), point(2.0f, 3.0f, -1.0f),
			make_shared<Metal>(make_shared<ConstantTexture>(rgb(color::LIGHTBLUE)), 0.0f)));
		//make_shared<Lambertian>(make_shared<ConstantTexture>(rgb(1.0f, 0.0f, 0.4f)))));

		scene.add(make_shared<Triangle>(point(-2.0f, 1.0f, -1.0f), point(0.0f, 2.0f, -1.0f), point(0.0f, 3.0f, -1.0f),
			make_shared<Metal>(make_shared<ConstantTexture>(color::YELLOW), 0.0f)));
		//make_shared<Lambertian>(make_shared<ConstantTexture>(color::YELLOW))));

		return scene;
	}

	HitableList fromObj(std::string file) {
		scene.clear();
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		std::shared_ptr<DiffuseLight> whiteLight = make_shared<DiffuseLight>(make_shared<ConstantTexture>(rgb(40.0f, 40.0f, 40.0f)));
		auto checker = make_shared<CheckerTexture>(make_shared<ConstantTexture>(rgb(0.2, 0.3, 0.6)), make_shared<ConstantTexture>(rgb(0.9, 0.9, 0.9)));


		scene.add(make_shared<Sphere>(point(0.0f, -100.5f, -1.0f), 100.0f,
			make_shared<Lambertian>(checker)));		// ground sphere
			//make_shared<Metal>(make_shared<ConstantTexture>(color::YELLOW), 0.0f)));

		scene.add(make_shared<Sphere>(point(-2.3f, 5.2f, 3.6f), 1.0f,
			//make_shared<Metal>(make_shared<ConstantTexture>(color::RED), 0.0f)));	
			whiteLight));

		scene.add(make_shared<Sphere>(point(-4.7f + 2.0f, 0.6f, 1.6f), 0.5f,
			make_shared<Metal>(make_shared<ConstantTexture>(color::RED), 0.0f)));	
			
		scene.add(make_shared<Sphere>(point(-4.7f + 5.0f, 0.6f - 0.6f, 1.6f), 0.5f,
			make_shared<Metal>(make_shared<ConstantTexture>(color::YELLOW), 0.0f)));

		scene.add(make_shared<Sphere>(point(-4.7f + 7.0f, 0.6f, 1.6f), 0.5f,
			make_shared<Metal>(make_shared<ConstantTexture>(color::GREEN), 0.0f)));


		std::shared_ptr<Lambertian> customDiffuse = make_shared<Lambertian>(make_shared<ConstantTexture>(color::LIGHTBLUE));
		std::shared_ptr<Metal> metal = make_shared<Metal>(make_shared<ConstantTexture>(color::GREEN), 0.0f);
		std::shared_ptr<Dielectric> dielectric = make_shared<Dielectric>(1.5f);
		std::shared_ptr<Material> material;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, file.c_str(), "scenes\\")) {
			throw std::runtime_error(warn + err);
		}
		std::cout << warn << '\n' << err << '\n';

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces/polygons(triangles in this case)
			size_t indexOffset = 0;

			for (size_t face = 0; face < shapes[s].mesh.num_face_vertices.size(); face++) {
				int fv = shapes[s].mesh.num_face_vertices[face];
				std::vector<point> points;
				std::vector<point> normals;

				// Loop over vertices in the face. fv will almost always be 3 as triangle primitives are being used.
				for (size_t v = 0; v < fv; v++) {
					tinyobj::index_t idx = shapes[s].mesh.indices[indexOffset + v];

					float vx = attrib.vertices[3 * idx.vertex_index + 0];
					float vy = attrib.vertices[3 * idx.vertex_index + 1];
					float vz = attrib.vertices[3 * idx.vertex_index + 2];
					points.push_back(point(vx, vy, vz));

					float nx = attrib.normals[3 * idx.normal_index + 0];
					float ny = attrib.normals[3 * idx.normal_index + 1];
					float nz = attrib.normals[3 * idx.normal_index + 2];
					normals.push_back(vec3(nx, ny, nz));
				}
				// Get the 3 vertices of triangle.
				point v0 = points[0];
				point v1 = points[1];
				point v2 = points[2];

				// Get vertex normals of triangle.
				vec3 n0 = normals[0];
				vec3 n1 = normals[1];
				vec3 n2 = normals[2];

				vec3 v0v1 = v1 - v0;
				vec3 v0v2 = v2 - v0;
				vec3 faceNormal = glm::normalize(glm::cross(v0v1, v0v2));

				int materialId = shapes[s].mesh.material_ids[face];
				if (materialId != -1) {
					tinyobj::material_t tinyMaterial = materials[materialId];

					rgb diffuseColor(tinyMaterial.diffuse[0], tinyMaterial.diffuse[1], tinyMaterial.diffuse[2]);
					rgb ambientColor(tinyMaterial.ambient[0], tinyMaterial.ambient[1], tinyMaterial.ambient[2]);
					material = make_shared<Lambertian>(make_shared<ConstantTexture>(diffuseColor));

					if (shapes[s].name.compare("area_light") == 0) material = whiteLight;
					if (shapes[s].name.compare("floor") == 0) material = metal;//make_shared<Metal>(make_shared<ConstantTexture>(color::YELLOW), 0.0f);
				}
				else {
					material = metal;
						//make_shared<Dielectric>(5.5f);
				}
				scene.add(make_shared<Triangle>(v0, v1, v2, material, n0, n1, n2));

				points.clear();
				normals.clear();
				indexOffset += fv;
			}
		}
		return scene;
	}




	HitableList randomScene() {
		// with BVH = 80 seconds	200X100X100 (W X H X SPP)
		// with BVH = y14341 seconds 640x480x1000
		using namespace mathStuff;
		scene.clear();
		scene.add(make_shared<Sphere>(
			point(0.0f, -1000.0f, 0.0f), 1000.0f, make_shared<Lambertian>(make_shared<ConstantTexture>(rgb(0.5f, 0.5f, 0.5f)))));

		int i = 1;
		for (int a = -11; a < 11; a++) {
			for (int b = -11; b < 11; b++) {
				float choose_mat = getRand();
				vec3 center(a + 0.9f * getRand(), 0.2f, b + 0.9f * getRand());
				if ((center - vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
					if (choose_mat < 0.8f) {
						// diffuse
						rgb albedo = randomVec3() * randomVec3();
						scene.add(
							make_shared<Sphere>(center, 0.2f, make_shared<Lambertian>(make_shared<ConstantTexture>(albedo))));
					}
					else if (choose_mat < 0.95f) {
						// metal
						vec3 albedo = randomVec3(.5f, 1.0f);
						float fuzz = getRand(0.0f, 0.5f);
						scene.add(make_shared<Sphere>(center, 0.2f, make_shared<Metal>(make_shared<ConstantTexture>(albedo), fuzz)));
						//world.add(make_shared<Triangle>(center + randomVec3(), center + randomVec3(), center + randomVec3(), make_shared<Metal>(albedo, fuzz)));
					}
					else {
						// glass
						scene.add(make_shared<Sphere>(center, 0.2f, make_shared<Dielectric>(1.5f)));
					}
				}
			}
		}

		scene.add(make_shared<Sphere>(vec3(0.0f, 1.0f, 0.0f), 1.0f, make_shared<Dielectric>(1.5f)));
		scene.add(make_shared<Sphere>(vec3(-4.0f, 1.0f, 0.0f), 1.0f, make_shared<Lambertian>(make_shared<ConstantTexture>(rgb(0.4f, 0.2f, 0.1f)))));

		scene.add(make_shared<Sphere>(vec3(4.0f, 1.0f, 0.0f), 1.0f, make_shared<Metal>(make_shared<ConstantTexture>(vec3(0.7f, 0.6f, 0.5f)), 0.0f)));

		return scene;
	}
}