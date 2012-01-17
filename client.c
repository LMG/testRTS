#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "client.h"
#include "graphics.h"
#include "game.h"

enum { NONE, RIGHT, LEFT, UP, DOWN };

int main(int argc, char *argv[])
{

    //init
   		printf("Random numbers initialization...\n");
		srand(time(NULL));
		printf("Done.\n");

		//network initialisation
		printf("Network intialization...\n");
		#if defined (WIN32)
		    WSADATA WSAData;
		    WSAStartup(MAKEWORD(2,2), &WSAData);
		#endif
		SOCKET sock = initNetwork();
		printf("Done.\n");
		//we are now connected

	   	//SDL initalisation
	   	printf("Graphics initialization...\n");
		SDL_Surface *screen = NULL;
		initSDL(&screen);
		printf("Done.\n");

		//game structures
		printf("Games structures initalization...\n");
		printf("Done.\n");

    	//receive the map from server
    	printf("Receiving the map from server...\n");
		struct map map;
		//do it with if(recv(sock, buffer, 10, 0)==SOCKET_ERROR)
		//map TODO: get it from the server
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
				map.tile[i][j].id=rand()%NB_TILES_TYPES;//random for now
				map.tile[i][j].entitie=NULL;
			}
		}
	   	printf("Done.\n");

	//main loop
    SDL_Event event;
    int keepPlaying = 1;
	int move=0;
	int direction=NONE;
	
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
		//receive key strokes
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


	   	//receive events from server => to do in another thread

	   	//update game structures
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

	   	//send events to server
		send(sock, "click", 5, 0);
		
	   	//print game
        game(screen, &map);
    }


    //cleanup
    SDL_Quit();

   	//closing socket
	shutdown(sock, 2);
	closesocket(sock);


    #if defined (WIN32)
        WSACleanup();
    #endif

	return EXIT_SUCCESS;
}

void* receiveData(void* threadData)
{
	//TODO...
}

SOCKET initNetwork()
{
	//socket creation
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    //socket's address
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

    while(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
    	printf("Connexion error\n");
    	sleep(1);
    }

    return sock;
}
