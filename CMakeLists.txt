cmake_minimum_required(VERSION 3.9)

project(raytracer)

set( SOURCES 
    # include files
    include/display/imagedisplay.h
    include/aabb.h
    include/bvh.h
    include/camera.h
    include/dielectric.h
    include/diffuselight.h
    include/hitable.h
    include/hitablelist.h
    include/lambertian.h
    include/material.h
    include/metal.h
    include/ray.h
    include/scenes.h
    include/sphere.h
    include/texture.h
    include/timer.h
    include/triangle.h
    include/utilities.h
    include/vec3aliases.h
    include/mesh.h

    # adding PGE as source helps if we want to edit the file in Visual Studio
    libs/pge/olcPixelGameEngine.h

    # same as above
    libs/tiny_obj/tiny_obj_loader.h

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
    src/mesh.cpp
    src/main.cpp
)
add_executable(raytracer_bin ${SOURCES})
target_include_directories(raytracer_bin PUBLIC "libs/glm" "include" "libs/pge" "libs/tiny_obj")

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(raytracer_bin PUBLIC OpenMP::OpenMP_CXX)
endif()

