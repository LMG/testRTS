#include "server.h"

int main(int argc, char* argv[])
{
	//for windows & the sockets
    #if defined (WIN32)
        WSADATA WSAData;
        WSAStartup(MAKEWORD(2,2), &WSAData);
    #endif
    
    //connexions status bits + client number, followed by the events flag + value for each client
    struct args args = {{0,0,0,0},0,{WAITING,WAITING,WAITING,WAITING},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	pthread_t thread[CLIENT_NB];
    
    //wait for the clients connexions
    clientConnexions(thread, &args);
	
	//game logic
	while(1)
	{
		printf("we play.\n");
		
		//retrieve events
		
		//modify game structures
		
		//send events to clients threads
		
		sleep(1);
	}
	
	//for windows & the sockets
    #if defined (WIN32)
        WSACleanup();
    #endif

    return EXIT_SUCCESS;
}

void clientConnexions(pthread_t thread[CLIENT_NB], struct args* args)
{
    int i;
    
	//the client's threads
	for(i=0; i<CLIENT_NB; i++)
	{
		printf("thread %d\n", i);
		pthread_create(&thread[i], NULL, manageClient, args);
	}
	
	while(!args->status[0] || !args->status[1] || !args->status[2] || !args->status[3])//wait until all clients are connected.
	{
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

//this function manage the clients and generates events for the game to handle
void* manageClient(void* rawArgs)
{
	//the client and servers sockets and their addresses
	SOCKET sock;
	SOCKADDR_IN sin;
	SOCKET csock;
	SOCKADDR_IN csin;
	
	struct args *args = (struct args *)rawArgs;
	int *clientReady = args->status;
	//getting number of the client and updating the variable.
	int num = args->clientNum;
	args->clientNum += 1;
	
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
		
		clientReady[num]=1;
		
		char buffer[10] = "test";
		send(csock, buffer, 10, 0);
	
		recv(csock, buffer, 10, 0);
		printf("received : %s\n", buffer);
		
		//game logic
		while(1)
		{
			//I NEED TO RETHINK THIS I DON'T KNOW HOW TO DO IT
			//retrieve game event sent by parent
			
			//send client event
			
			//retrieve game event sent by client
			
			//send parent event
		}
	}
	
	shutdown(csock, 2);
	shutdown(sock, 2);
	closesocket(csock);
	closesocket(sock);
	
	return NULL;
}