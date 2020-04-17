#pragma warning(disable : 26454)
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <float.h>
#include <omp.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <chrono>
#include <ray.h>
#include <utilities.h>
#include <sphere.h>
#include <hitableList.h>
#include <hitable.h>
#include <camera.h>
#include <material.h>
#include <lambertian.h>
#include <metal.h>
#include <triangle.h>
#include <dielectric.h>
#include <vec3aliases.h>
#include <bvh.h>
#include <texture.h>
#include <timer.h>
#include <display/imagedisplay.h>
#include <thread>
#include <diffuselight.h>

constexpr int MAX_REFLECTS = 50;
constexpr float TMIN = 0.001f;
constexpr float TMAX = FLT_MAX;

// returns a color for a given ray
vec3 ray_color(const Ray &r, const rgb background, const Hitable& world, int depth) {
	using namespace color;
	hitRecord record;		

	if (depth <= 0) return BLACK;

	if (!world.hit(r, TMIN, TMAX, record)) return background;

	Ray scattered;
	rgb attenuation;
	rgb emitted = record.materialPtr->emitted(record.u, record.v, record.p);
	if (!record.materialPtr->scatter(r, record, attenuation, scattered))
		return emitted;

	return emitted + attenuation * ray_color(scattered, background, world, depth - 1);
	
	//if (world.hit(r, TMIN, FLT_MAX, record)) {
	//	Ray scattered;
	//	vec3 attenuation;
	//	if (depth < MAX_REFLECTS && record.materialPtr->scatter(r, record, attenuation, scattered)) {
	//		return attenuation * ray_color(scattered, world, depth + 1);
	//	}
	//	else {
	//		return BLACK;
	//	}
	//}
	//else {
	////generate background gradient
	//vec3 unitDirection = glm::normalize(r.direction());
	////squish t between 0 and 1
	//float t = 0.5f * (unitDirection.y + 1.0f);		// mathStuff::squish(t, -1, 1);		
	//// lerp according to up/downness	
	//return mathStuff::lerp(WHITE, LIGHTBLUE, t);
	//}
}

void saveImage(std::vector<uint8_t> image, int width, int height, int spp) {
	std::ofstream  raytracedImage;
	std::ostringstream file;
	file << width << " x " << height << "_spp_" << spp << "_reflects_" << MAX_REFLECTS << ".ppm";
	std::cout << "Creating output file : " << file.str() << '\n';
	raytracedImage.open(file.str());
	raytracedImage << "P3\n" << width << " " << height << "\n255\n";

	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width; ++i) {
			raytracedImage << static_cast<int>(image[3 * (j * width + i) + 0]) << " ";
			raytracedImage << static_cast<int>(image[3 * (j * width + i) + 1]) << " ";
			raytracedImage << static_cast<int>(image[3 * (j * width + i) + 2]) << '\n';
		}
	}
	raytracedImage.close();
}

HitableList ballScene() {
	using std::make_shared;
	HitableList scene;

	std::shared_ptr<DiffuseLight> whiteLight = make_shared<DiffuseLight>(make_shared<ConstantTexture>(color::WHITE));
	auto checker = make_shared<CheckerTexture>(make_shared<ConstantTexture>(rgb(0.2, 0.3, 0.1)), make_shared<ConstantTexture>(rgb(0.9, 0.9, 0.9)));
	scene.add(make_shared<Sphere>(point(0.0f, -100.5f, -1.0f), 100.0f, make_shared<Lambertian>(checker)));		// ground sphere

	scene.add(make_shared<Sphere>(point(1.0f, 0.0f, -1.0f), 0.5f, make_shared<Metal>(rgb(0.2f, 0.8f, 0.2f), 0.0f)));
	scene.add(make_shared<Sphere>(point(-2.0f, 1.0f, 1.0f), 1.0f, make_shared<Metal>(rgb(1.0f, 0.2f, 0.7f), 0.0f)));
	scene.add(make_shared<Sphere>(point(-1.0f, 0.0f, -1.0f), 0.5f, make_shared<Dielectric>(1.5f)));
	scene.add(make_shared<Sphere>(point(-1.0f, 0.0f, -1.0f), -0.45f,
		whiteLight));
	//make_shared<Dielectric>(1.5f)));
	scene.add(make_shared<Sphere>(point(0.0f, .0f, -1.0f), -0.5f, make_shared<Dielectric>(1.7f)));

	scene.add(make_shared<Triangle>(point(0.0f, 1.0f, -1.0f), point(2.0f, 2.0f, -1.0f), point(2.0f, 3.0f, -1.0f), make_shared<Metal>(rgb(1.0f, 0.2f, 0.7f), 0.0f)));
	//make_shared<Lambertian>(make_shared<ConstantTexture>(rgb(1.0f, 0.0f, 0.4f)))));
	scene.add(make_shared<Triangle>(point(-2.0f, 1.0f, -1.0f), point(0.0f, 2.0f, -1.0f), point(0.0f, 3.0f, -1.0f), make_shared<Lambertian>(make_shared<ConstantTexture>(rgb(0.2f, 0.3f, 0.4f)))));
	return scene;
}


int main() { 

	using std::make_shared;
	using namespace mathStuff;
	Timer timer;

	int width = 640;			// width
	int height = 480;			// height
	int spp = 10;				// number of samples per pixel

	std::vector<uint8_t> image(width * height * 3); // width * height * 3 RGB channels
	ImageDisplay display(width, height, &image);
	auto displayThread = std::thread(&ImageDisplay::startDisplay, &display);

	vec3 lookFrom(3.0, 3.0, 2.0);
	vec3 lookAt(0.0, 0.0, -1.0);
	vec3 vUp(0.0,1.0,0.0);
	float distToFocus = glm::length(lookFrom - lookAt);
	float aperture = 0.01f;
	Camera camera(lookFrom, lookAt, vUp, 90, float(width) / float(height), aperture, distToFocus);
	
	HitableList world = ballScene();
	BvhNode bvhRoot(world);
	//BvhNode bvhRoot(randomScene());
	
	timer.start("rendering");
	#pragma omp parallel for collapse(2)
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {		
			rgb col(0, 0, 0);
			for (int s = 0; s < spp; s++) {
				float u = float(i + getRand()) / float(width);
				float v = float(j + getRand()) / float(height);
				Ray r = camera.getRay(u, v);
				point p = r.pointAtParameter(2.0);
				col += ray_color(r, color::BLACK, world, MAX_REFLECTS);
			}
			col /= float(spp);
			col = rgb(sqrt(col.r), sqrt(col.g), sqrt(col.b));	// gamma correction
			image[3 * (j*width + i) + 0] = static_cast<int>(256 * clamp(col.r, 0.0f, 0.999f));
			image[3 * (j*width + i) + 1] = static_cast<int>(256 * clamp(col.g, 0.0f, 0.999f));
			image[3 * (j*width + i) + 2] = static_cast<int>(256 * clamp(col.b, 0.0f, 0.999f));

		}
	}
	timer.end();
	timer.start("file writing");
	saveImage(image, width, height, spp);
	timer.end();
	displayThread.join();
	return 0;
}



/* TODO
Read settings from file at runtime
*/

/*
HitableList randomScene() {
	// with BVH = 80 seconds	200X100X100 (W X H X SPP)
	// with BVH = y14341 seconds 640x480x1000
	HitableList world;
	using std::make_shared;
	using namespace mathStuff;
	world.add(make_shared<Sphere>(
		vec3(0.0f, -1000.0f, 0.0f), 1000.0f, make_shared<Lambertian>(vec3(0.5f, 0.5f, 0.5f))));

	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = getRand();
			vec3 center(a + 0.9f * getRand(), 0.2f, b + 0.9f * getRand());
			if ((center - vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
				if (choose_mat < 0.8f) {
					// diffuse
					vec3 albedo = randomVec3() * randomVec3();
					world.add(
						make_shared<Sphere>(center, 0.2f, make_shared<Lambertian>(albedo)));
				}
				else if (choose_mat < 0.95f) {
					// metal
					vec3 albedo = randomVec3(.5f, 1.0f);
					float fuzz = getRand(0.0f, 0.5f);
					world.add(make_shared<Sphere>(center, 0.2f, make_shared<Metal>(albedo, fuzz)));
					//world.add(make_shared<Triangle>(center + randomVec3(), center + randomVec3(), center + randomVec3(), make_shared<Metal>(albedo, fuzz)));
				}
				else {
					// glass
					world.add(make_shared<Sphere>(center, 0.2f, make_shared<Dielectric>(1.5f)));
				}
			}
		}
	}

	world.add(make_shared<Sphere>(vec3(0.0f, 1.0f, 0.0f), 1.0f, make_shared<Dielectric>(1.5f)));

	world.add(make_shared<Sphere>(vec3(-4.0f, 1.0f, 0.0f), 1.0f, make_shared<Lambertian>(vec3(0.4f, 0.2f, 0.1f))));

	world.add(make_shared<Sphere>(vec3(4.0f, 1.0f, 0.0f), 1.0f, make_shared<Metal>(vec3(0.7f, 0.6f, 0.5f), 0.0f)));

	return world;
}


*/