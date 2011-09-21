#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"

#define DELAY 25

int main(int argc, char *argv[])
{
	//initialization of the SDL.
    SDL_Surface *screen = NULL;
	initSDL(&screen);
			
	//main loop
    SDL_Event event;
    int keepPlaying = 1;
    SDL_Rect origin = {0,0};
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
        
        game(screen, &origin, &value);
        
        //waiting
        SDL_Delay(DELAY);
    }
    
    SDL_Quit();

    return EXIT_SUCCESS;
}
