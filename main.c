#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"

#define DELAY 25

int main(int argc, char *argv[])
{
	//initialization of the SDL.
    SDL_Surface *screen = NULL;
	initSDL(&screen);
	
	//tiling 
	SDL_Surface *tile = IMG_Load("ressources/tile_001.png");
	SDL_SetColorKey(tile, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 221, 0, 221));
	SDL_Rect origin_tile = {0, (tile->h/2)};
	SDL_Surface *tile2 = IMG_Load("ressources/tile_002.png");
	SDL_SetColorKey(tile2, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 221, 0, 221));
	SDL_Rect origin_tile2 = {0, tile2->h-(tile->h/2)};
    SDL_Rect origin = {0,0};
    SDL_Rect boardSize = {30,30};
		
	//main loop
    SDL_Event event;
    int keepPlaying = 1;
    
    int value = 0;//stupid test

    while (keepPlaying)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                keepPlaying = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        keepPlaying = 0;
                        break;
                    case SDLK_RIGHT:
                    	origin.x +=5;
                    	break;
                   	case SDLK_LEFT:
                    	origin.x -=5;
                   		break;
                   	case SDLK_UP:
                    	origin.y -=5;
                   		break;
                   	case SDLK_DOWN:
                    	origin.y +=5;
                   		break;
                   	//stupid test
                   	case SDLK_a:
                   		value++;
                   		break;
                   	case SDLK_z:
                   		value--;
                   		break;
                    default: 
                    	break;
                }
                break;
           default:
            	break;
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
        		if((x^y)>value)//TODO:insert the real test with the matrix instead of this stupid test
        		{
        			position.x = origin.x+(y+x)*(tile->w/2)-origin_tile2.x;
		    		position.y = origin.y+(-y+x)*(tile->h/2)-origin_tile2.y; //we makes the y and x position correspond with the origin of the tile.
		    		SDL_BlitSurface(tile2, NULL, screen, &position);
		    	}
		    	else
		    	{
		    		position.x = origin.x+(y+x)*(tile->w/2)-origin_tile.x;
		    		position.y = origin.y+(-y+x)*(tile->h/2)-origin_tile.y; //we makes the y and x position correspond with the origin of the tile.
		    		SDL_BlitSurface(tile, NULL, screen, &position);
		    	}
        	}
        }
        
        //updating the screen
        SDL_Flip(screen);
        
        //waiting
        SDL_Delay(DELAY);
    }
    
    SDL_Quit();

    return EXIT_SUCCESS;
}
