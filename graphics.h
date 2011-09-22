#ifndef DEF_GRAPHICS
#define DEF_GRAPHICS

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>

#define WINDOW_HEIGHT 512
#define WINDOW_WIDTH 1024

#define TILE_HEIGHT 25
#define TILE_WIDTH 48

#define NB_TILES 6

//initialization of the SDL.
void initSDL (SDL_Surface **screen);
void game (SDL_Surface *screen, SDL_Rect* origin, int *value);

#endif
