cmake_minimum_required(VERSION 3.7)

project(raytracer)

file(GLOB SOURCES "*.h" "*.cpp" )

add_executable(main ${SOURCES} "Aabb.cpp" "Bvh.cpp")

target_include_directories(main PUBLIC "libs/glm")

