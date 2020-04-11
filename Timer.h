#pragma once
#include <chrono>
#include <string>
#include <iostream>

class Timer {
public:

	Timer() {}

	inline void start(std::string taskName) {
		task = taskName;
		std::cout << "Starting timer for task : " << task << "\n";
		startTime = std::chrono::high_resolution_clock::now();
	}
	
	inline void end() {
		auto end = std::chrono::high_resolution_clock::now();
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - startTime);
		auto minutes = std::chrono::duration_cast<std::chrono::minutes>(end - startTime);
		auto hours = std::chrono::duration_cast<std::chrono::hours>(end - startTime);
		std::cout << task << " took " << seconds.count() << " seconds, " << minutes.count() << " minutes, " << hours.count() << " hours.\n" ;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	std::string task;
};