// Structs and Constants
#include "vectors.h"
#include "matrix.h"
#include "objects.h"
#include "constants.h"

// Functions
#include "skybox.h"
#include "shader.h"
#include "viewport.h"
#include "putPixel.h"

// External Library
#include "SDL.h"

// Standard Library
#include <array>
#include <iostream>

// For Mesuring Rendering Time
#include <chrono>

namespace constants {
	Object objList[numberofObjects];
	Light lightList[numberofLights];
}

int main(void){

    constants::objList[0] = Object({0, -1, 3}, 1, 's', {255, 0, 0}, 500, 0.2);
    constants::objList[1] = Object({2, 0.0, 4.0}, 1, 's', {0, 0, 255}, 500, 0.3);
    constants::objList[2] = Object({-2, 0, 4}, 1, 's', {0, 255, 0}, 10, 0.4);
    constants::objList[3] = Object({0, -5001, 0}, 5000, 's', {255, 255, 0}, 1000, 0.5);

    constants::lightList[0] = Light('a', 0.2, {0 ,0 ,0}, {255, 0, 0});
    constants::lightList[1] = Light('p', 0.6, {2 ,1 ,0}, {255, 0, 0});
    constants::lightList[2] = Light('d', 0.2, {1, 4, 4}, {255, 0, 0});

    auto start = std::chrono::high_resolution_clock::now();

	Vector3D<double> viewportCamera {0, 0, 0};

	// yaw, pitch, and roll
	// https://en.wikipedia.org/wiki/Rotation_matrix
	Vector3D<double> CameraRotation {0, 0, 0}; //0.785
	double rotationMat[3][3];
	rotationMatrix(CameraRotation, rotationMat);

	SDL_Event event; // Basic Event Union
	SDL_Window* window = NULL; // The Window we will be rendering to

	// Test the Skybox
	const char * skyboxFaces[] = {"assets/images/posx.jpg", 
											  "assets/images/negx.jpg", 
											  "assets/images/posy.jpg", 
											  "assets/images/negy.jpg", 
											  "assets/images/posz.jpg", 
											  "assets/images/negz.jpg"};
	// Now initialize the skybox
	initializeSkybox(skyboxFaces, 6);

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

	SDL_LockSurface( screenSurface );

	for(int y = -constants::SCREEN_HEIGHT / 2; y < constants::SCREEN_HEIGHT / 2; y++){
		#pragma omp parallel for schedule(static)
		for(int x = -constants::SCREEN_WIDTH / 2; x < constants::SCREEN_WIDTH / 2; x++){
			Vector3D<double> viewportCoordinates = CanvasToViewport(x, y).MatMul(rotationMat).normalize();
			Vector3D<int> color = TraceRay(viewportCamera, viewportCoordinates, 1, std::numeric_limits<double>::max(), constants::RECURSION_DEPTH);
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

	// Free the skybox Images
	freeSkybox();

	return 0;
}


