# Raytracer

A (backwards) raytracer I wrote for learning. 

- Using [GLM](https://glm.g-truc.net/) for vector math.
- Using CMake for building and portability.
- Using OpenMP for parallelization.
- Using [OneLoneCoder's](http://www.onelonecoder.com/) incredibly helpful [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine) for display. 

References used : 
- [Peter Shirley's Raytracing Series](https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf)
- [PBRT](http://www.pbr-book.org/)
- [Scratchapixel](https://www.scratchapixel.com/)

## TODO : 
- [X] Implement Bounding Volume Hierarchies.
- [X] Parallelize.
- [ ] Study [PBRT's](https://www.pbrt.org/) architecture.
- [ ] Study/contribute to the Mitsuba renderer.

### Example output : diffuse, dielectric and metallic materials with triangle primitives
![Example output : diffuse, dielectric and metallic materials](https://github.com/manas96/Raytracer/blob/master/demo.jpg)
