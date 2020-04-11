cmake_minimum_required(VERSION 3.9)

project(raytracer)

file(GLOB SOURCES "*.h" "*.cpp" )

add_executable(main ${SOURCES} "Aabb.cpp" "Bvh.cpp")

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(main PUBLIC OpenMP::OpenMP_CXX)
endif()


target_include_directories(main PUBLIC "libs/glm")

