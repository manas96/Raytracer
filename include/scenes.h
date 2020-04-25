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

		scene.add(make_shared<Sphere>(point(1.0f, 0.0f, -1.0f), 0.5f, make_shared<Metal>(rgb(0.2f, 0.8f, 0.2f), 0.0f)));

		scene.add(make_shared<Sphere>(point(-2.0f, 1.0f, 1.0f), 1.0f,
			//whiteLight));
		make_shared<Metal>(rgb(1.0f, 0.2f, 0.7f), 0.0f)));

		scene.add(make_shared<Sphere>(point(-1.0f, 0.0f, -1.0f), 0.5f, make_shared<Dielectric>(1.5f)));

		scene.add(make_shared<Sphere>(point(-1.0f, 0.0f, -1.0f), -0.45f,
			//whiteLight));
			make_shared<Dielectric>(1.5f)));

		//scene.add(make_shared<Sphere>(point(0.0f, .0f, -1.0f), -0.5f, make_shared<Dielectric>(1.7f)));

		scene.add(make_shared<Triangle>(point(-2.0f + 1, 1.0f, -1.0f), point(0.0f + 1, 2.0f, -1.0f), point(0.0f + 1, 3.0f, -1.0f),
			make_shared<Lambertian>(make_shared<ConstantTexture>(color::GREEN))));

		scene.add(make_shared<Triangle>(point(0.0f, 1.0f, -1.0f), point(2.0f, 2.0f, -1.0f), point(2.0f, 3.0f, -1.0f),
			//make_shared<Metal>(rgb(1.0f, 0.2f, 0.7f), 0.0f)));
		make_shared<Lambertian>(make_shared<ConstantTexture>(rgb(1.0f, 0.0f, 0.4f)))));

		scene.add(make_shared<Triangle>(point(-2.0f, 1.0f, -1.0f), point(0.0f, 2.0f, -1.0f), point(0.0f, 3.0f, -1.0f),
		//	make_shared<Metal>(color::YELLOW, 0.0f)));
		make_shared<Lambertian>(make_shared<ConstantTexture>(color::YELLOW))));

		return scene;
	}

	HitableList fromObj(std::string file) {
		scene.clear();
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		std::shared_ptr<DiffuseLight> whiteLight = make_shared<DiffuseLight>(make_shared<ConstantTexture>(rgb(1000.0f, 1000.0f, 1000.0f)));

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, file.c_str(), "scenes\\")) {
			throw std::runtime_error(warn + err);
		}
		std::cout << warn << '\n' << err << '\n';

		std::shared_ptr<Material> material = make_shared<Lambertian>(make_shared<ConstantTexture>(color::YELLOW));		
		std::shared_ptr<Metal> fadedMetal = make_shared<Metal>(rgb(0.5f, 0.4f, 0.2f), 0.0f);
		std::shared_ptr<Metal> yellowMetal = make_shared<Metal>(color::YELLOW, 0.0f);
		std::shared_ptr<Dielectric> glass = make_shared<Dielectric>(1.6f);


		scene.add(make_shared<Sphere>(point(0.0f, -100.5f, -1.0f), 100.0f,
			fadedMetal));		// ground sphere

		std::vector<point> points;
		std::vector<point> normals;
		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				// vertex coords
				float vx = attrib.vertices[3 * index.vertex_index + 0];
				float vy = attrib.vertices[3 * index.vertex_index + 1];
				float vz = attrib.vertices[3 * index.vertex_index + 2];
				points.push_back(point(vx, vy, vz));

				float nx = attrib.normals[3 * index.normal_index + 0];
				float ny = attrib.normals[3 * index.normal_index + 1];
				float nz = attrib.normals[3 * index.normal_index + 2];
				normals.push_back(point(nx, ny, nz));
			}
			int verticesPerFace = shape.mesh.num_face_vertices[0];		// this will be same for all faces since faces are triangulated
			for (int i = 0; i < shape.mesh.indices.size() - verticesPerFace; i = i + verticesPerFace) {

				// calculate face normal from vertex normals
				vec3 v0 = points[i];
				vec3 v1 = points[i + 1];
				vec3 v2 = points[i + 2];
				
				
				vec3 v0v1 = v1 - v0;
				vec3 v0v2 = v2 - v0;
				vec3 faceNormal = glm::normalize(glm::cross(v0v1, v0v2));

				scene.add(make_shared<Triangle>(v0, v1, v2, glass, faceNormal));
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
						scene.add(make_shared<Sphere>(center, 0.2f, make_shared<Metal>(albedo, fuzz)));
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

		scene.add(make_shared<Sphere>(vec3(4.0f, 1.0f, 0.0f), 1.0f, make_shared<Metal>(vec3(0.7f, 0.6f, 0.5f), 0.0f)));

		return scene;
	}
}