//Structs and Constants
#include "custom/include/constants.h"
#include "custom/include/shapes.h"
#include "custom/include/vectors.h"

// Functions
#include "custom/include/shader.h"
#include "custom/include/vectormath.h"
#include "custom/include/viewport.h"
#include "custom/include/putPixel.h"

// External Library
#include "external/SDL2/include/SDL.h"

// Standard Library
#include <iostream>

// For Mesuring Rendering Time
#include <chrono>

int main(void){

    auto start = std::chrono::high_resolution_clock::now();

	VEC::VECTOR3D viewportCamera({0 ,0 ,0});

	SDL_Event event; // Basic Event Union
	SDL_Window* window = NULL; // The Window we will be rendering to

	// Surface gives Blit Access to Pixels on CPU
	// SDL_Renderer works on GPU 
	SDL_Surface* screenSurface = NULL; // The Surface that fills the Window

	// Starting up Video System of SDL
	// https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidebasicsinit.html
	if(SDL_Init(SDL_INIT_VIDEO)<0){ // Call to function also Initiliasize it
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
		return -1;
	}

	// The Actual Window
	window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	// Check If window Pointer got created
	if(window == NULL){
		std::cout << "Window could not be created! SDL_Error: " <<  SDL_GetError() << "\n";
		return -1;
	}

	// Create the Surface to which we will draw
	screenSurface = SDL_GetWindowSurface(window);
	
	int numberofObjects = 4;
	shapes::SPHERE objList[numberofObjects];

	objList[0] = shapes::initSphere({0.0, -1.0, 3.0}, 1, {255, 0, 0}, 500, 0.2);

	objList[1] = shapes::initSphere({2.0, 0.0, 4.0}, 1, {0, 0, 255}, 500, 0.3);

	objList[2] = shapes::initSphere({-2.0, 0.0, 4.0}, 1, {0, 255, 0}, 10, 0.4);

	objList[3] = shapes::initSphere({0.0, -5001.0, 0.0}, 5000, {255, 255, 0}, 1000, 0.5);
	
	int numberofLights = 3;
	shader::Light lightList[numberofLights];

	lightList[0] = shader::initLight('a', 0.2, {0 ,0 ,0}, {255, 0, 0});

	lightList[1] = shader::initLight('p', 0.6, {2 ,1 ,0}, {255, 0, 0});

	lightList[2] = shader::initLight('d', 0.2, {1 ,4 ,4}, {255, 0, 0});


	SDL_LockSurface( screenSurface );

	for(int y = -constants::SCREEN_HEIGHT / 2; y < constants::SCREEN_HEIGHT / 2; y++){
		for(int x = -constants::SCREEN_WIDTH / 2; x < constants::SCREEN_WIDTH / 2; x++){
			VEC::VECTOR3D viewportCoordinates = viewport::CanvasToViewport(x, y);
			VEC::VECTOR3Di color = viewport::TraceRay(viewportCamera, viewportCoordinates, 1, 100000000, objList, numberofObjects, lightList, numberofLights, constants::RECURSION_DEPTH);
			putPixel(screenSurface, x, y, SDL_MapRGB(screenSurface->format, color.x, color.y, color.z));
		}
	}

	SDL_UnlockSurface( screenSurface );
	SDL_UpdateWindowSurface(window);

	auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time Taken to Render: " << duration.count() / (double)1000000 << " s\n";
	// Game Loop
	while(1){
        if(SDL_PollEvent(&event) && event.type == SDL_QUIT){
            break;
		}
	}

	return 0;
}


