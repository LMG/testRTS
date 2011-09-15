#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

//initialization of the SDL.
void initSDL (SDL_Surface **screen)
{
	SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(IMG_Load("ressources/icon.png"), NULL); // The icon needs to be loaded before calling SDL_SetVideoMode
    *screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("JEU", NULL);
}
