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
    
	static SDL_Surface *tile[NB_TILES];
	static SDL_Rect origin_tile[NB_TILES];
	static SDL_Rect boardSize;
	
	if(!init)
	{
		init =1;
		
		int i;
		
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
		
		boardSize.x = 3;
		boardSize.y = 4;
		
		printf("Init done \n");
	}
	
	// erasing the screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    //blitting the tiles TODO: load the tiles from a matrix
    int x, y, n, i, numberOfLine = (boardSize.x+boardSize.y-1) ;
    SDL_Rect position;
    for (n=1; n<=numberOfLine; n++)
    {
  		printf("%d\n", n);
    	if(n>=boardSize.y)
    	{
    		y=boardSize.y-1;
    		x=n-boardSize.y;
    	}
    	else
    	{
    		y=n-1;
    		x=0;
    	}
    	for(i=0; i<n && i<boardSize.x && i<boardSize.y; i++)
    	{
    		printf("x,y = %d,%d\n", x, y);
    		y--;
    		x++;
    		if((x^y)>*value)//TODO:insert the real test with the matrix instead of this stupid test
			{
				position.x = origin->x+(x-y)*(TILE_WIDTH/2)-origin_tile[3].x;
				position.y = origin->y+(y+x)*(TILE_HEIGHT/2)-origin_tile[3].y; //we makes the y and x position correspond with the origin of the tile.
				SDL_BlitSurface(tile[3], NULL, screen, &position);
			}
			else
			{
				position.x = origin->x+(x-y)*(TILE_WIDTH/2)-origin_tile[2].x;
				position.y = origin->y+(y+x)*(TILE_HEIGHT/2)-origin_tile[2].y; //we makes the y and x position correspond with the origin of the tile.
				SDL_BlitSurface(tile[2], NULL, screen, &position);
			}
    	}
    	
    	/*
    	//
    	if(boardSize.x-n>0)
    	{
    		x=boardSize.x-n;
    	}
    	else
    	{
    		x=0;
    	}
    	for(y=0;x<boardSize.x&&y<=n;x++,y++)
    	{
			//printf("x,y = %d,%d\n", x, y);
			if((x^y)>*value)//TODO:insert the real test with the matrix instead of this stupid test
			{
				position.x = origin->x+(x-y)*(TILE_WIDTH/2)-origin_tile[3].x;
				position.y = origin->y+(y+x)*(TILE_HEIGHT/2)-origin_tile[3].y; //we makes the y and x position correspond with the origin of the tile.
				SDL_BlitSurface(tile[3], NULL, screen, &position);
			}
			else
			{
				position.x = origin->x+(x-y)*(TILE_WIDTH/2)-origin_tile[2].x;
				position.y = origin->y+(y+x)*(TILE_HEIGHT/2)-origin_tile[2].y; //we makes the y and x position correspond with the origin of the tile.
				SDL_BlitSurface(tile[2], NULL, screen, &position);
			}
    	}
    	*/
    }
    
    
    //updating the screen
    SDL_Flip(screen);
}
