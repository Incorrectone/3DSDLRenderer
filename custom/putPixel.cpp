#include "include/putPixel.h"
#include "include/constants.h"
#include "../external/SDL2/include/SDL.h"

int putPixel(SDL_Surface* surface, int canvasX, int canvasY, Uint32 color){
	if(canvasX > (constants::SCREEN_WIDTH / 2) || canvasX < -(constants::SCREEN_WIDTH / 2))
		return -1;
	if(canvasY > (constants::SCREEN_HEIGHT / 2) || canvasY < -(constants::SCREEN_HEIGHT / 2))
		return -1;
	
	// Pg. 3
	int screenX = (constants::SCREEN_WIDTH / 2) + canvasX;
	int screenY = (constants::SCREEN_HEIGHT / 2) + canvasY;

	Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                             + screenY * surface->pitch
                                             + screenX * surface->format->BytesPerPixel);
	*target_pixel = color;
	return 0;
}