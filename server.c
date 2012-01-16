#include "server.h"

int main(int argc, char* argv[])
{
	//for windows & the sockets
    #if defined (WIN32)
        WSADATA WSAData;
        WSAStartup(MAKEWORD(2,2), &WSAData);
    #endif
    
    //game structures
    struct map map;
	pthread_t thread[CLIENT_NB];
    
    //wait for the clients connexions
    clientConnexions(thread, &map);
	
	//game logic
	int play=1;
	while(play)
	{
		printf("we play.\n");
		
		//retrieve events
		
		//modify game structures
		
		//send events to clients threads
		
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

void clientConnexions(pthread_t thread[CLIENT_NB], struct map* map)
{
    int client;
    struct threadData threadDataArray[CLIENT_NB];
    
	//the client's threads
	for(client=0; client<CLIENT_NB; client++)
	{
		printf("thread %d\n", client);
		//data shared with the thread
		threadDataArray[client].id=client;
		threadDataArray[client].map=map;
		threadDataArray[client].status=0;
		pthread_create(&thread[client], NULL, manageClient, (void*)&threadDataArray[client]);
	}
	
	int everybodyIsConnected=0;
	while(!everybodyIsConnected)//wait until all clients are connected.
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
	//everybody is connected
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

//thread function: this function manage the clients and updates the game structures according to what it receives.
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
	
	else
	{
		//silly tests
		printf("Client %d connected\n", num);
		
		myData->status=1;
		
		char buffer[10] = "test";
		send(csock, buffer, 10, 0);
	
		recv(csock, buffer, 10, 0);
		printf("received : %s\n", buffer);
		
		//game logic
		while(1)
		{
			//retrieve game event sent by client
			
			//update games structures
		}
	}
	
	shutdown(csock, 2);
	shutdown(sock, 2);
	closesocket(csock);
	closesocket(sock);
	
	return NULL;
}
