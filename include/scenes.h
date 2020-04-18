#include <hitablelist.h>
#include <sphere.h>
#include <triangle.h>
#include <metal.h>
#include <lambertian.h>
#include <dielectric.h>
#include <utilities.h>

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
		scene.add(make_shared<Sphere>(point(0.0f, .0f, -1.0f), -0.5f, make_shared<Dielectric>(1.7f)));

		//scene.add(make_shared<Triangle>(point(0.0f, 1.0f, -1.0f), point(2.0f, 2.0f, -1.0f), point(2.0f, 3.0f, -1.0f), make_shared<Metal>(rgb(1.0f, 0.2f, 0.7f), 0.0f)));
		//make_shared<Lambertian>(make_shared<ConstantTexture>(rgb(1.0f, 0.0f, 0.4f)))));
		//scene.add(make_shared<Triangle>(point(-2.0f, 1.0f, -1.0f), point(0.0f, 2.0f, -1.0f), point(0.0f, 3.0f, -1.0f),
		//	make_shared<Metal>(color::YELLOW, 0.0f)));
		//make_shared<Lambertian>(make_shared<ConstantTexture>(color::YELLOW))));
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