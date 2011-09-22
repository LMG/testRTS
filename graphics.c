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

void game (SDL_Surface *screen, struct map* map)
{
	//initialisation
	static int init = 0;
    
	static SDL_Surface *tile[NB_TILES];
	static SDL_Rect origin_tile[NB_TILES];
		
	int i;
	
	if(!init)
	{
		init =1;
		
		for(i=0; i<NB_TILES; i++)
		{
			char name[24] = "ressources/tile_";
			sprintf(name, "%s%03d%s", name, i, ".png");
			printf("%s\n", name);
			tile[i] = IMG_Load(name);
			SDL_SetColorKey(tile[i], SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 221, 0, 221));
			origin_tile[i].x = 0;
			origin_tile[i].y = tile[i]->h-TILE_HEIGHT;
		}
		
		printf("Init done \n");
	}
	
	// erasing the screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    //blitting the tiles
    int x, y, n, numberOfLine = (map->sizeX+map->sizeY-1) ;
    SDL_Rect position;
    for (n=1; n<=numberOfLine; n++)
    {
    	if(n>=map->sizeY)
    	{
    		y=map->sizeY-1;
    		x=n-map->sizeY;
    	}
    	else
    	{
    		y=n-1;
    		x=0;
    	}
    	for(i=0; i<n && i<map->sizeX && i<map->sizeY && x<map->sizeX-1 && y>0; i++)
    	{
    		y--;
    		x++;
    		
			position.x = map->origin.x+(x-y)*(TILE_WIDTH/2)-origin_tile[map->tile[x][y]].x;
			position.y = map->origin.y+(y+x)*(TILE_HEIGHT/2)-origin_tile[map->tile[x][y]].y; //we makes the y and x position correspond with the origin of the tile.
			SDL_BlitSurface(tile[map->tile[x][y]], NULL, screen, &position);
    	}
    }
    
    
    //updating the screen
    SDL_Flip(screen);
}
