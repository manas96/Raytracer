#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
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
#include "Dielectric.h"
#define MAX_REFLECTS 50


// returns a color for a given ray
glm::vec3 color(const Ray &r, Hitable *world, int depth) {
	hitRecord record;		//record.p is the pointAt() parameter

	if (world->hit(r, 0.001, FLT_MAX, record)) {
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

	int nx = 200;			//width
	int ny = 100;			//height
	int ns = 100;			//number of samples to take within each pixle. increase for better antialiasing 
	Camera camera(glm::vec3(-2,2,1), glm::vec3(0,0,-1), glm::vec3(0,1,0), 45, float(nx) / float(ny));

	std::ofstream  renderedImage;
	std::ostringstream file;
	file << nx << " x " << ny << "_pixelAverage_" << ns << "_reflects_"<< MAX_REFLECTS << ".ppm";
	renderedImage.open(file.str());
	renderedImage << "P3\n" << nx << " " << ny << "\n255\n";

	const int MAX_OBJECTS = 5;
	Hitable* list[MAX_OBJECTS];
	list[0] = new Sphere(glm::vec3(0, 0, -1), 0.5, new Lambertian(glm::vec3(0.1, 0.2, 0.5)));
	list[1] = new Sphere(glm::vec3(0, -100.5, -1), 100, new Lambertian(glm::vec3(0.8, 0.8, 0.0)));
	list[2] = new Sphere(glm::vec3(1, 0, -1), 0.5, new Metal(glm::vec3(0.8, 0.6, 0.2), 0));
	list[3] = new Sphere(glm::vec3(-1, 0, -1), 0.5, new Dielectric(1.5));
	list[4] = new Sphere(glm::vec3(-1, 0, -1), -0.45, new Dielectric(1.5));
	Hitable* world = new HitableList(list, MAX_OBJECTS);
	

	auto start = std::chrono::high_resolution_clock::now();

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {		
			glm::vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + mathStuff::getRand()) / float(nx);
				float v = float(j + mathStuff::getRand()) / float(ny);
				Ray r = camera.getRay(u, v);
				glm::vec3 p = r.pointAtParameter(2.0);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = glm::vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));	// gamma correction : TODO optimize later
			int ir = int(255.99 * col.x);
			int ig = int(255.99 * col.y);
			int ib = int(255.99 * col.z);
			renderedImage << ir << " " << ig << " " << ib << "\n";
		}
	}
	renderedImage.close();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout << "Render time : " << duration.count() << " seconds." << std::endl;

	return 0;
}