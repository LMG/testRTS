#ifndef DEF_GRAPHICS
#define DEF_GRAPHICS

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

#define TILE_HEIGHT 25
#define TILE_WIDTH 48

#define NB_TILES 10
#define NB_ENTITIES 1

struct map {
	SDL_Rect origin;
	int sizeX;
	int sizeY;
	struct tile **tile;
};

struct tile {
	int id;
	struct entitie* entitie;
};

struct entitie {
	int id;
	int x;
	int y;
	struct entitie* next;
};

//initialization of the SDL.
void initSDL (SDL_Surface **screen);
void game (SDL_Surface *screen, struct map* map);

#endif
