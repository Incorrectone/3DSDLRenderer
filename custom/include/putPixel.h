#pragma once

#ifndef putPixel_H
#define putPixel_H

#include "../../external/SDL2/include/SDL.h"

int putPixel(SDL_Surface* surface, int canvasX, int canvasY, Uint32 color);

#endif