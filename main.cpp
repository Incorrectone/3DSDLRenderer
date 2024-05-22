//Structs and Constants
#include "custom/include/constants.h"
#include "custom/include/shapes.h"
#include "custom/include/vectors.h"

// Functions
#include "custom/include/shader.h"
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

	Vector3D<double> viewportCamera {0 ,0 ,0};

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
	
	const int numberofObjects = 3;
	Object objList[numberofObjects];

	objList[0] = Object({1.0, 0.0, 1.0}, 10, 'p', {192, 192, 192}, 500, 0.9);

	objList[1] = Object({1.0, 0.0, -1.0}, -10, 'p', {192, 192, 192}, 500, 0.9);

	objList[2] = Object({0.0, -1.0, 7.0}, 1, 's', {255, 0, 0}, 500, 0.3);

	const int numberofLights = 3;
	Light * lightList = (Light *)malloc(sizeof(Light) * numberofLights);

	lightList[0] = Light('a', 0.6, {0 ,0 ,0}, {255, 0, 0});

	lightList[1] = Light('p', 0.6, {2 ,1 ,0}, {255, 0, 0});

	lightList[2] = Light('d', 0.2, {1 ,4 ,4}, {255, 0, 0});


	SDL_LockSurface( screenSurface );

	for(int y = -constants::SCREEN_HEIGHT / 2; y < constants::SCREEN_HEIGHT / 2; y++){
		for(int x = -constants::SCREEN_WIDTH / 2; x < constants::SCREEN_WIDTH / 2; x++){
			Vector3D<double> viewportCoordinates = viewport::CanvasToViewport(x, y);
			Vector3D<int> color = viewport::TraceRay(viewportCamera, viewportCoordinates, 1, std::numeric_limits<double>::max(), objList, numberofObjects, lightList, numberofLights, constants::RECURSION_DEPTH);
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


