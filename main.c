#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graphics.h"

enum { NONE, RIGHT, LEFT, UP, DOWN };

int main(int argc, char *argv[])
{
	//initialization of the SDL.
    SDL_Surface *screen = NULL;
	initSDL(&screen);
	srand(time(NULL));//to test the tiles.
			
	//main loop
    SDL_Event event;
    int keepPlaying = 1;
	int move=0;
	int direction=NONE;
	
	//map
	struct map map;
	map.origin.x = 0;
	map.origin.y = 0;
	map.sizeX = 200;
	map.sizeY = 200;
	map.tile = malloc(map.sizeX*sizeof(struct tile*));
	int i, j;
	for(i=0; i<map.sizeX; i++)
	{
		map.tile[i] = malloc(map.sizeY*sizeof(struct tile));
		for(j=0; j<map.sizeY; j++)
		{
			map.tile[i][j].id=rand()%NB_TILES;//random for now
			map.tile[i][j].entitie=NULL;
		}
	}
	
	//entities
	int nbEntities = 2;
	map.tile[5][5].entitie=malloc(sizeof(struct entitie));
	struct entitie *current = map.tile[5][5].entitie;
	current->id = 0;
	current->x = 5;
	current->y = 5;
	for(i=1; i<nbEntities; i++)
	{
		current->next = malloc(sizeof(struct entitie));
		current = current->next;
		current->id = 0;
		current->x = 6;
		current->y = 6;
	}
	current->next = NULL;
	
    while (keepPlaying)
    {
        while(SDL_PollEvent(&event))
        {
		    switch(event.type)
		    {
				// button press
				case SDL_MOUSEBUTTONDOWN:
					move = 1;
					switch(event.button.button)
					{
						case SDL_BUTTON_LEFT:
							move = 1;
							break;
					}
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
		                	direction=RIGHT;
		                	break;
		               	case SDLK_LEFT:
		                	direction=LEFT;
		               		break;
		               	case SDLK_UP:
		                	direction=UP;
		               		break;
		               	case SDLK_DOWN:
		                	direction=DOWN;
		               		break;
		                default: 
		                	break;
		            }
		            break;
		         case SDL_KEYUP:
		         	switch(event.key.keysym.sym)
		         	{
		         		case SDLK_RIGHT:
		         			if (direction==RIGHT)
		         				direction=NONE;
		         			break;
		         		case SDLK_LEFT:
		         			if (direction==LEFT)
		         				direction=NONE;
		         			break;
		         		case SDLK_UP:
		         			if (direction==UP)
		         				direction=NONE;
		         			break;
		         		case SDLK_DOWN:
		         			if (direction==DOWN)
		         				direction=NONE;
		         			break;
		         		default:
		         			break;
		         	}
		         	break;
		       default:
		        	break;
		    }
		}
		
		//moving the entitie
		if(direction==UP)
		{
			map.tile[5][5].entitie->y -=1;
		}
		if(direction==DOWN)
		{
			map.tile[5][5].entitie->y +=1;
		}
		if(direction==LEFT)
		{
			map.tile[5][5].entitie->x -=1;
		}
		if(direction==RIGHT)
		{
			map.tile[5][5].entitie->x +=1;
		}
		
        game(screen, &map);
    }
    
    SDL_Quit();

    return EXIT_SUCCESS;
}
