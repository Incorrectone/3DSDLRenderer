#include "putPixel.h"
#include "constants.h"
#include "SDL.h"

// Basic Pixel Changing function
void putPixel(SDL_Surface* surface, int canvasX, int canvasY, Uint32 color){
    int screenX = (constants::SCREEN_WIDTH / 2) + canvasX;
    int screenY = (constants::SCREEN_HEIGHT / 2) - canvasY - 1; // Added -1 here

    if(screenX < 0 || screenX >= surface->w || screenY < 0 || screenY >= surface->h) {
        return; 
    }

    Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                             + screenY * surface->pitch
                                             + screenX * surface->format->BytesPerPixel);
    *target_pixel = color;
}