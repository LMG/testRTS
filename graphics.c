#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

//initialization of the SDL.
void initSDL (SDL_Surface **screen)
{
	SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(IMG_Load("ressources/icon.png"), NULL); // The icon needs to be loaded before calling SDL_SetVideoMode
    *screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
    SDL_WM_SetCaption("JEU", NULL);
}

void game (SDL_Surface *screen, struct map* map)
{
	//initialisation
	static int init = 0;
    
	static SDL_Surface *tile[NB_TILES];
	static SDL_Rect origin_tile[NB_TILES];
	static SDL_Surface *entitie[NB_ENTITIES];
	static SDL_Rect origin_entitie[NB_ENTITIES];
	
	//load ressources
	int i;
	if(!init)
	{
		init =1;
		
		for(i=0; i<NB_TILES; i++)
		{
			char name[24] = "ressources/tile_";
			sprintf(name, "%s%03d%s", name, i, ".png");
			printf("%s\n", name);//debug
			tile[i] = IMG_Load(name);
			SDL_SetColorKey(tile[i], SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 221, 0, 221));
			origin_tile[i].x = 0;
			origin_tile[i].y = tile[i]->h-TILE_HEIGHT;
		}
		
		for(i=0; i<NB_ENTITIES; i++)
		{
			char name[24] = "ressources/char_";
			sprintf(name, "%s%03d%s", name, i, ".png");
			printf("%s\n", name);//debug
			entitie[i] = IMG_Load(name);
			SDL_SetColorKey(entitie[i], SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 221, 0, 221));
			origin_entitie[i].x = 0;
			origin_entitie[i].y = entitie[i]->h;
		}
		
		printf("Init done \n");
	}
	
	// erasing the screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    //blitting the tiles
    int x, y, n, numberOfLine = (map->sizeX+map->sizeY-1) ;
    SDL_Rect position, position2;
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
    	for(i=0; i<n && i<map->sizeX && i<map->sizeY && x<map->sizeX && y>=0; i++)
    	{
    		
    		//first the tile
			position.x = map->origin.x+(x-y)*(TILE_WIDTH/2)-origin_tile[map->tile[x][y].id].x;
			position.y = map->origin.y+(y+x)*(TILE_HEIGHT/2)-origin_tile[map->tile[x][y].id].y; //we make the y and x position correspond with the origin of the tile.
			SDL_BlitSurface(tile[map->tile[x][y].id], NULL, screen, &position);
			
			//then the eventual entitie
			struct entitie *current = map->tile[x][y].entitie;
			while(current != NULL)
			{
				position2.x = position.x + current->x-origin_entitie[current->id].x;
				position2.y = position.y + current->y-origin_entitie[current->id].y;
				SDL_BlitSurface(entitie[current->id], NULL, screen, &position2);
				current = current->next;
			}
			
    		y--;
    		x++;
    	}
    }
    
    
    //updating the screen
    SDL_Flip(screen);
}
