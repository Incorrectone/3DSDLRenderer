#pragma once

#ifndef putPixel_H
#define putPixel_H

#include "../../external/SDL2/include/SDL.h"

/*  
    Automatically Converts Canvas Coordinates into Screen Coordinates
    Use SDL_MapRGB or SDL_MapRGBA to have color the Screen Surface->Format 
*/
void putPixel(SDL_Surface* surface, int canvasX, int canvasY, Uint32 color);

#endif