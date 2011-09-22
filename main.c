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
	int move=0;
	
	//map
	struct map map;
	map.origin.x = 0;
	map.origin.y = 0;
	map.sizeX = 10;
	map.sizeY = 10;
	map.tile = malloc(map.sizeX*sizeof(int*));
	int i, j;
	for(i=0; i<map.sizeX; i++)
	{
		map.tile[i] = malloc(map.sizeY*sizeof(int));
		for(j=0; j<map.sizeY; j++)
		{
			map.tile[i][j]=(i+j)%NB_TILES;
		}
	}
	
    while (keepPlaying)
    {
        while(SDL_PollEvent(&event))
        {
		    switch(event.type)
		    {
				// button press
				case SDL_MOUSEBUTTONDOWN:
					move = 1;
					break;
				case SDL_MOUSEBUTTONUP:
					move = 0;
					break;			
				case SDL_MOUSEMOTION:
					if(move==1)
					{
						map.origin.x = map.origin.x+event.motion.xrel;
						map.origin.y = map.origin.y+event.motion.yrel;
					}
					break;								
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
		                	map.origin.x +=5;
		                	break;
		               	case SDLK_LEFT:
		                	map.origin.x -=5;
		               		break;
		               	case SDLK_UP:
		                	map.origin.y -=5;
		               		break;
		               	case SDLK_DOWN:
		                	map.origin.y +=5;
		               		break;
		                default: 
		                	break;
		            }
		            break;
		       default:
		        	break;
		    }
		}    
        game(screen, &map);
        
        //waiting
        //SDL_Delay(DELAY);
    }
    
    SDL_Quit();

    return EXIT_SUCCESS;
}
