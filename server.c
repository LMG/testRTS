#include <string.h>
#include "server.h"
#include "game.h"

int main(int argc, char* argv[])
{
	//for windows & the sockets
    #if defined (WIN32)
        WSADATA WSAData;
        WSAStartup(MAKEWORD(2,2), &WSAData);
    #endif
    
    
 	//random map generation
 	srand(time(NULL));
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
			map.tile[i][j].id=rand()%NB_TILES_TYPES;//random for now
			map.tile[i][j].entitie=NULL;
		}
	}
 	
    //flags
    struct flags flags = {0,0};
    
    //threads
	pthread_t thread[CLIENT_NB];
	struct threadData dataClient[CLIENT_NB];
	int client;
	for(client=0; client<CLIENT_NB; client++)
	{
		//data shared with the thread
		dataClient[client].id=client;
		dataClient[client].map=&map;
		dataClient[client].status=0;
		dataClient[client].flags=&flags;
		dataClient[client].sock=0;
	}
    
    //waiting for the clients connexions
    clientConnexions(thread, dataClient);
	
	//send map
	char buffer[BUFFER_SIZE];
	for(client=0; client<CLIENT_NB; client++)
	{
		sprintf(buffer, "morig%3d%3d\n", map.origin.x, map.origin.y);
		send(dataClient[client].sock, buffer, 12, 0);
		for(i=0; i<map.sizeX; i++)
		{
			for(j=0; j<map.sizeY; j++)
			{
				//send
			}
		}
	}	
	
	//game logic
	int play=1;
	while(play)
	{
		printf("we play.\n");
		
		//check for map modifications and send them to clients
		if(flags.mapModified)
		{
			flags.mapModified=0;
			//TODO: actually send modifications.
			for(client=0; client<CLIENT_NB; client++)
			{
				//send
			}
		}
		
		sleep(1);
	}
	
	//cleanup
	closeConnexions(thread);
	
	//for windows & the sockets
    #if defined (WIN32)
        WSACleanup();
    #endif

    return EXIT_SUCCESS;
}

void clientConnexions(pthread_t thread[CLIENT_NB], struct threadData threadDataArray[CLIENT_NB])
{
    int client;
    
	//the client's threads
	for(client=0; client<CLIENT_NB; client++)
	{
		printf("thread %d\n", client);
		pthread_create(&thread[client], NULL, manageClient, (void*)&threadDataArray[client]);
	}
	
	//wait until all clients are connected.
	int everybodyIsConnected=0;
	while(!everybodyIsConnected)
	{
		everybodyIsConnected=1;
		for(client=0; client<CLIENT_NB; client++)
		{
			if(threadDataArray[client].status==0)
				everybodyIsConnected=0;				
		}
		printf("waiting for the connexions....\n");
		sleep(1);
	}
}

void closeConnexions(pthread_t thread[CLIENT_NB])
{
	int i;
	
	//waiting for the connexions end.
	for(i=0; i<CLIENT_NB; i++)
	{
		void* returnValue;
		pthread_join(thread[i], &returnValue);
	}
}

//thread function: this function manage the clients and updates the game structures according to what it receives. It is only for reception.
void* manageClient(void* threadData)
{
	//the client and servers sockets and their addresses
	SOCKET sock;
	SOCKADDR_IN sin;
	SOCKET csock;
	SOCKADDR_IN csin;
	
	struct threadData * myData = (struct threadData *)threadData;
	
	//getting number of the client and updating the variable.
	int num = myData->id;
	
	printf("Client %d\n", num);
	
	//socket creation
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == SOCKET_ERROR)
	{
		printf("Error during connexion of client %d: socket creation\n", num);
		return NULL;
	}
	
	//preparation of the server address context
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	
	//client socket's  address
	csin.sin_addr.s_addr = htonl(INADDR_ANY);
	csin.sin_family = AF_INET;
	csin.sin_port = htons(PORT);
	
	//setting up the client socket's address
	while(bind(sock, (SOCKADDR*)&sin, sizeof(sin))==SOCKET_ERROR)
	{
		printf("Awaiting connexion of client %d\n", num);
		sleep(1);
	}
	//listenning and accepting connexion
	if(listen(sock, 5)==SOCKET_ERROR)
	{
		printf("Connexion error ! (listenning) \n");
		return NULL;
	}
	socklen_t size = sizeof(csin);
	csock = accept(sock, (SOCKADDR*) &csin, &size);
	if(csock == INVALID_SOCKET)
	{
		printf("Connexion error ! (client socket) \n");
		return NULL;
	}
	
	//we are connected.
	printf("Client %d connected\n", num);
	
	myData->sock=csock;
	
	//we are ready
	myData->status=1;
	
	//receive event and update game structures
	char buffer[BUFFER_SIZE];
	while(1)
	{
		//retrieve game event sent by client
		recv(csock, buffer, 10, 0);
			
		//TODO: have a buffer updated up to a closing character	
			
		//update games structures accordingly
		if(strncmp(buffer, "click", 5)==0)
		{
			printf("click !!\n");
		}
	}
	
	shutdown(csock, 2);
	shutdown(sock, 2);
	closesocket(csock);
	closesocket(sock);
	
	return NULL;
}
