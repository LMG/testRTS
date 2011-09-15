#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"

#define DELAY 100

int main(int argc, char *argv[])
{
	//initialization of the SDL.
    SDL_Surface *screen = NULL;
	initSDL(&screen);
	
	//tiling 
	SDL_Surface *tile = IMG_Load("ressources/tile_001.png");
	SDL_SetColorKey(tile, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 221, 0, 221));
		
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
                    	break;
                   	case SDLK_LEFT:
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
        
        //blitting the tiles TODO: do it right :D
        int x, y;
        SDL_Rect position;
        for (x=0; x<(screen->w); x+=tile->w)
        {
        	for (y=0; y<(screen->h); y+=tile->h)
        	{
        		position.x = x;
        		position.y = y;
        		SDL_BlitSurface(tile, NULL, screen, &position);
        	}
        }
        for (x=tile->w/2; x<(screen->w); x+=tile->w)
        {
        	for (y=tile->h/2; y<(screen->h); y+=tile->h)
        	{
        		position.x = x;
        		position.y = y;
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
