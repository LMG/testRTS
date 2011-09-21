#ifndef DEF_GRAPHICS
#define DEF_GRAPHICS

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define WINDOW_HEIGHT 512
#define WINDOW_WIDTH 1024

//initialization of the SDL.
void initSDL (SDL_Surface **screen);
void game (SDL_Surface *screen, SDL_Rect* origin, int *value);

#endif
