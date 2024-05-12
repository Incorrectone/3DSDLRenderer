#include "custom/include/constants.h"
#include "custom/include/putPixel.h"
#include "external/SDL2/include/SDL.h"
#include <stdio.h>

int main(void){
	SDL_Event event; // Basic Event Union
	SDL_Window* window = NULL; // The Window we will be rendering to

	// Surface gives Blit Access to Pixels on CPU
	// SDL_Renderer works on GPU 
	SDL_Surface* screenSurface = NULL; // The Surface that fills the Window

	// Starting up Video System of SDL
	// https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidebasicsinit.html
	if(SDL_Init(SDL_INIT_VIDEO)<0){ // Call to function also Initiliasize it
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}

	// The Actual Window
	window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	// Check If window Pointer got created
	if(window == NULL){
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	// Create the Surface to which we will draw
	screenSurface = SDL_GetWindowSurface(window);

	//Fill the surface white
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	
	putPixel(screenSurface, 0, 0, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

	//Update the surface
	SDL_UpdateWindowSurface(window);


	// Game Loop
	while(1){
        if(SDL_PollEvent(&event) && event.type == SDL_QUIT){
            break;
		}
    }

	return 0;
}


