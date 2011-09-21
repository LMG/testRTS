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

void game (SDL_Surface *screen, SDL_Rect* origin, int *value)
{
	//initialisation
	static int init = 0;
    
	static SDL_Surface *tile;
	static SDL_Rect origin_tile;
	static SDL_Surface *tile2;
	static SDL_Rect origin_tile2;
	static SDL_Rect boardSize;
	
	if(!init)
	{
		init =1;
		
		tile = IMG_Load("ressources/tile_001.png");
		SDL_SetColorKey(tile, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 221, 0, 221));
		origin_tile.x = 0;
		origin_tile.y = tile->h/2;
		
		tile2 = IMG_Load("ressources/tile_002.png");
		SDL_SetColorKey(tile2, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 221, 0, 221));
		origin_tile2.x = 0;
		origin_tile2.y = tile2->h-(tile->h/2);
		
		boardSize.x = 30;
		boardSize.y = 30;
		
		printf("Init done \n");
	}
	
	// erasing the screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    //blitting the tiles TODO: load the tiles from a matrix
    int x, y;
    SDL_Rect position;
    for (x=0; x<boardSize.x; x++)
    {
    	for (y=0; y<boardSize.y; y++)
    	{
    		if((x^y)>*value)//TODO:insert the real test with the matrix instead of this stupid test
    		{
    			position.x = origin->x+(y+x)*(tile->w/2)-origin_tile2.x;
	    		position.y = origin->y+(-y+x)*(tile->h/2)-origin_tile2.y; //we makes the y and x position correspond with the origin of the tile.
	    		SDL_BlitSurface(tile2, NULL, screen, &position);
	    	}
	    	else
	    	{
	    		position.x = origin->x+(y+x)*(tile->w/2)-origin_tile.x;
	    		position.y = origin->y+(-y+x)*(tile->h/2)-origin_tile.y; //we makes the y and x position correspond with the origin of the tile.
	    		SDL_BlitSurface(tile, NULL, screen, &position);
	    	}
    	}
    }
    
    //updating the screen
    SDL_Flip(screen);
}
