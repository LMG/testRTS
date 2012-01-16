#ifndef DEF_GRAPHICS
#define DEF_GRAPHICS

#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include "game.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

//initialization of the SDL.
void initSDL (SDL_Surface **screen);
void game (SDL_Surface *screen, struct map* map);

#endif
