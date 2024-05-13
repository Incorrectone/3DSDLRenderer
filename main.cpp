//Structs and Constants
#include "custom/include/constants.h"
#include "custom/include/shapes.h"

// Functions
#include "custom/include/viewport.h"
#include "custom/include/putPixel.h"

// External Library
#include "external/SDL2/include/SDL.h"

// Standard Library
#include <iostream>
#include <tuple>
#include <vector>

int main(void){
	std::vector<double> viewportCamera({0 ,0 ,0});

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
	
	int numberofObjects = 3;
	shapes::SPHERE objList[numberofObjects];

	objList[0] = shapes::initSphere({0.0, -1.0, 3.0}, 1, std::make_tuple(255, 0, 0));

	objList[1] = shapes::initSphere({2.0, 0.0, 4.0}, 1, std::make_tuple(0, 0, 255));

	objList[2] = shapes::initSphere({-2.0, 0.0, 4.0}, 1, std::make_tuple(0, 255, 0));

	SDL_LockSurface( screenSurface );

	for(int y = -constants::SCREEN_HEIGHT / 2; y < constants::SCREEN_HEIGHT / 2; y++){
		for(int x = -constants::SCREEN_WIDTH / 2; x < constants::SCREEN_WIDTH / 2; x++){
			std::vector<double> viewportCoordinates = viewport::CanvasToViewport(x, y);
			std::tuple<int, int, int> color = viewport::TraceRay(viewportCamera, viewportCoordinates, 1, 100000000, objList, numberofObjects);
			putPixel(screenSurface, x, y, SDL_MapRGB(screenSurface->format, std::get<0>(color), std::get<1>(color), std::get<2>(color)));
		}
	}

	putPixel(screenSurface, 0, 0, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
	SDL_UnlockSurface( screenSurface );
	SDL_UpdateWindowSurface(window);

	std::cout << "DONE\n";
	// Game Loop
	while(1){
        if(SDL_PollEvent(&event) && event.type == SDL_QUIT){
            break;
		}
    }

	return 0;
}


