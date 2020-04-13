cmake_minimum_required(VERSION 3.9)

project(raytracer)

set( SOURCES 
    # source code files
    src/aabb.cpp
    src/bvh.cpp
    src/camera.cpp
    src/dielectric.cpp
    src/hitablelist.cpp
    src/lambertian.cpp
    src/metal.cpp
    src/sphere.cpp
    src/triangle.cpp
    src/utilities.cpp
    src/main.cpp
)
add_executable(raytracer_bin ${SOURCES})
target_include_directories(raytracer_bin PUBLIC "libs/glm" "include" "libs/pge")

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(raytracer_bin PUBLIC OpenMP::OpenMP_CXX)
endif()

