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
    SDL_Rect origin = {0,0};
    SDL_Rect boardSize = {30,30};
		
	//main loop
    SDL_Event event;
    int keepPlaying = 1;

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
        		position.x = origin.x+(y+x)*(tile->w/2);
        		position.y = origin.y+(-y+x)*(tile->h/2)-(tile->h/2); //we substract the height of the tile to fit the corner of the first square to the origin.
        		SDL_BlitSurface(tile, NULL, screen, &position);
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
