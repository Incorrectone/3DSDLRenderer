# Basic C++ SDL2 project

This project is a basic C++ [SDL2][SDL] project that uses [CMake][] as a build system.

To build either run the shell scripts in the order configure -> build -> run, or just run all.sh once.

This was made to learn about basics of Computer graphics, C++, CMake, and simple Bash scripting with the help of the book by [Gabriel Gambetta](https://gabrielgambetta.com/computer-graphics-from-scratch/index.html)

## TO-DO

Orignally I wanted to learn how rendering math worked, but as I read through and found more interest in raytracing

So the goal has expanded, I still plan to make rasterization in the engine but that comes after learning how to render a semi accurate black hole. Regardless of how much math and Physics I need to learn.

### Goals
Will update and make them detailed as I learn about it.

- [ ] Finish Gabriel Gambetta books Raytracing last chapter tasks
- [ ] Implement basic black hole mechanics
    - [ ] Introduce gravity mechanics.
    - [ ] Deploy basic gravity affected ray tracing methods.
    - [ ] Catch up on the basic mathematics needed for the task.
    - [ ] Introduce a sky box for better viewing of the black hole.
    - [ ] Add distorting effect of light.
- [ ] Implement the accretion disk (Currently following and seeing on some tutorials that the accretion disks can just be a thin plane)
    - [ ] Introduce volumetrics to the engine.
    - [ ] Create shaders/some equivalent for custom volumetrics.
    - [ ] Use the introduced volumetrics to create an accretion disk.
- [ ] Introduce Movement, for simple animations 
    - [ ] Movement of camera.
    - [ ] (if possible) Movement of objects including volumetrics.
- [ ] Introduce planets
    - [ ] Sphere but with normals and depth.
    - [ ] Somehow introduce atmosphere (volumetric or simpler.)
- [ ] Introduce better cmake configurations for debug and production builds.
- [ ] Introduce parallelism
    - [ ] Use multiple cores in CPU.
    - [ ] Use GPU accelration.
- [ ] Start the work on rasterization.

## Dependencies

- [Git][]
- C/C++ Compiler (gcc, g++, ...)
- [CMake][]
- [SDL2.30][SDL] library

**On Debian/Ubuntu based distributions, use the following command:**

```sh
sudo apt install git build-essential pkg-config cmake cmake-data libsdl2-dev
```
<!--
**Optional packages:**

- [SDL2_image][] library
- [SDL2_ttf][] library
- [SDL2_net][] library
- [SDL2_mixer][] library
- [SDL2_gfx][] library

```sh
sudo apt install libsdl2-image-dev libsdl2-ttf-dev libsdl2-net-dev libsdl2-mixer-dev libsdl2-gfx-dev
```
-->

## Build instructions

```sh
# Clone this repo
git clone https://github.com/Incorrectone/3DSDLRenderer.git
cd SDLProject

# Create a build folder
mkdir build
cd build

# Build
cmake -S ..
make

# Run
./Renderer
```
<!--

***Note:*** To use SDL2_image, SDL2_ttf, SDL2_net, SDL2_mixer or SDL2_gfx, you
should uncomment some instructions in the CMakeLists.txt file and re-execute
the `make` command.

### Open the project with an IDE under Linux

See [IDE_USAGE.md](IDE_USAGE.md) for details.

-->
## License (idk why this is here)

Author: incorrectone

This project is distributed under the terms of the MIT license
[&lt;LICENSE&gt;](LICENSE).



[SDL]: https://www.libsdl.org
[CMake]: https://cmake.org
[Git]: https://git-scm.com
[SDL2_image]: https://www.libsdl.org/projects/SDL_image
[SDL2_ttf]: https://www.libsdl.org/projects/SDL_ttf
[SDL2_net]: https://www.libsdl.org/projects/SDL_net
[SDL2_mixer]: https://www.libsdl.org/projects/SDL_mixer
[SDL2_gfx]: http://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx
