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
#include <scenes.h>

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

int main() { 

	using std::make_shared;
	using namespace mathStuff;
	Timer timer;

	int width = 100;			// width
	int height = 100;			// height
	int spp = 5;				// number of samples per pixel

	std::vector<uint8_t> image(width * height * 3); // width * height * 3 RGB channels
	ImageDisplay display(width, height, &image);
	auto displayThread = std::thread(&ImageDisplay::startDisplay, &display);

	//vec3 lookFrom(0.0, 2.0, 1.0); // cornell
	vec3 lookFrom(1.0f, 3.0f, 4.0f);
	vec3 lookAt(0.0, 1.9, -1.0);
	vec3 vUp(0.0,1.0,0.0);
	float distToFocus = 100.0f;
	float aperture = 0.0f;
	Camera camera(lookFrom, lookAt, vUp, 90, float(width) / float(height), aperture, distToFocus);
	
	timer.start("geometry loading");
	
		//HitableList world = scenes::exampleScene();
		//HitableList world = scenes::fromObj("scenes/cornell-empty.obj");
		HitableList world = scenes::fromObj("../scenes/teapot_hires.obj");
		//HitableList world = scenes::fromObj("../scenes/dragon.obj");
		//HitableList world = scenes::fromObj("scenes\\conference.obj");
	
	timer.end();

	timer.start("BVH construction");
	BvhNode bvhRoot(world);
	timer.end();

	timer.start("rendering");
	#pragma omp parallel for collapse(2)
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {		
			rgb col(0, 0, 0);
			for (int s = 0; s < spp; s++) {
				float u = float(i + getRand()) / float(width);
				float v = float(j + getRand()) / float(height);
				Ray r = camera.getRay(u, v);
				col += ray_color(r, rgb(0.4,0.4,0.4), bvhRoot, MAX_REFLECTS);
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
	std::cout << "Done.\n";

	return 0;
}



/* TODO
Read settings from file at runtime
*/
