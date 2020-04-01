#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <float.h>
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include <chrono>
#include "Ray.h"
#include "Utilities.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Hitable.h"
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Triangle.h"
#include "Dielectric.h"
#define MAX_REFLECTS 50
#define TMIN 0.001
#define TMAX FLT_MAX


// returns a color for a given ray
glm::vec3 color(const Ray &r, Hitable *world, int depth) {
	hitRecord record;		//record.p is the pointAt() parameter

	if (world->hit(r, TMIN, FLT_MAX, record)) {
		Ray scattered;
		glm::vec3 attenuation;
		if (depth < MAX_REFLECTS && record.materialPtr->scatter(r, record, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return BLACK;
		}
	}
	else {
	//--------------generate background gradient-----------------------------
	glm::vec3 unitDirection = glm::normalize(r.direction());
	//squish t between 0 and 1
	float t = 0.5f * (unitDirection.y + 1.0f);		// mathStuff::squish(t, -1, 1);		
	// lerp according to up/downness	
	return mathStuff::lerp(WHITE, LIGHTBLUE, t);
	}
}

int main() { 
	typedef glm::vec3 point;
	typedef glm::vec3 rgb;
	typedef glm::vec3 vector3;

	int nx = 640;			//width
	int ny = 480;			//height
	int ns = 100;			//number of samples to take within each pixle. increase for better antialiasing 

	vector3 lookFrom(3.0, 3.0, 2.0);
	vector3 lookAt(0.0, 0.0, -1.0);
	vector3 vUp(0.0,1.0,0.0);
	float distToFocus = glm::length(lookFrom - lookAt);
	float aperture = 0.1f;
	Camera camera(lookFrom, lookAt, vUp, 90, float(nx) / float(ny), aperture, distToFocus);

	std::ofstream  raytracedImage;
	std::ostringstream file;
	file << nx << " x " << ny << "_pixelAverage_" << ns << "_reflects_"<< MAX_REFLECTS << ".ppm";
	std::cout << "Creating output file : " << file.str() << '\n';
	raytracedImage.open(file.str());
	raytracedImage << "P3\n" << nx << " " << ny << "\n255\n";
	const int MAX_OBJECTS = 5;
	Hitable* list[MAX_OBJECTS];
	list[0] = new Sphere(point(0.0, 0.0, -1.0), 0.5, new Lambertian(rgb(1, 0.2, 0.5)));
	list[0] = new Triangle(point(0.0, 1.0, -1), point(2.0, 2.0, -1), point(2.0, 3.0, -1), new Lambertian(rgb(1.0, 0.0, 0.4)));

	list[1] = new Sphere(point(0.0, -100.5, -1.0), 100, new Lambertian(rgb(0.8, 0.8, 0.0)));	//ground ball
	list[2] = new Sphere(point(1.0, 0.0, -1.0), 0.5, new Metal(rgb(0.2, 0.8, 0.2), 0));
	
	list[3] = new Sphere(point(-1, 0, -1), 0.5, new Dielectric(1.5));
	list[4] = new Sphere(point(-1, 0, -1), -0.45, new Dielectric(1.5));
	Hitable* world = new HitableList(list, MAX_OBJECTS);
	


	// Hitable* world = randomScene();

	auto start = std::chrono::high_resolution_clock::now();

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {		
			//std::cout << "Currently on pixel (" << i << ", "<< j << ")"<< std::endl;	// slows processing significantly, should not be used
			rgb col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + mathStuff::getRand()) / float(nx);
				float v = float(j + mathStuff::getRand()) / float(ny);
				Ray r = camera.getRay(u, v);
				point p = r.pointAtParameter(2.0);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = rgb(sqrt(col.r), sqrt(col.g), sqrt(col.b));	// gamma correction : TODO optimize later
			int ir = int(255.99 * col.r);
			int ig = int(255.99 * col.g);
			int ib = int(255.99 * col.b);
			raytracedImage << ir << " " << ig << " " << ib << "\n";
		}
	}
	raytracedImage.close();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout << "Render time : " << duration.count() << " seconds." << std::endl;

	return 0;
}
/* TODO
Read settings from file at runtime
parallelize 
implement BVH

Hitable* randomScene() {
	using namespace glm;
	using namespace mathStuff;
	int n = 500;
	Hitable** list = new Hitable* [n + 1];
	list[0] = new Sphere(vec3(0, -1000, 0), 1000, new Lambertian(vec3(.5, .5, .5)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float chooseMaterial = getRand();
			vec3 center(a + .9f * getRand(), .2f, b + .9f * getRand());
			if (length((center - vec3(4, .2, 0))) > .9f) {
				if (chooseMaterial < .8) {
					list[i++] = new Sphere(center, 0.2, new Lambertian(vec3(getRand() * getRand(), getRand() * getRand(), getRand() * getRand())));
				}
				else if (chooseMaterial < .95) {
					list[i++] = new Sphere(center, 0.2, new Metal(vec3(.5f * (1 + getRand()), .5f * (1 + getRand()), .5f * (1 + getRand())), .5f * getRand()));
				}
				else {
					list[i++] = new Sphere(center, .2, new Dielectric(1.5));
				}
			}
		}
	}
	list[i++] = new Sphere(vec3(0, 1, 0), 1.0f, new Dielectric(1.5));
	list[i++] = new Sphere(vec3(-4, 1, 0), 1.0f, new Lambertian(vec3(.4, .2, .1)));
	list[i++] = new Sphere(vec3(4, 1, 0), 1.0f, new Metal(vec3(.7, .6, .5), 0));

	return new HitableList(list, i);
}





*/

