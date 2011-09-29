#include "client.h"

int main(int argc, char *argv[])
{
	#if defined (WIN32)
        WSADATA WSAData;
        WSAStartup(MAKEWORD(2,2), &WSAData);
    #endif
	
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
    //we are now connected
    
    //silly test
	//receive
	char buffer[10];
	if(recv(sock, buffer, 10, 0)==SOCKET_ERROR)
	{
		printf("Reception error\n");
   	}
   	else
   	{
   		printf("Received : %s\n", buffer);
   	}
   	
   	//send
   	strcpy(buffer, "prout");   	
   	if(send(sock, buffer, 10, 0)==SOCKET_ERROR)
   	{
   		printf("Sending error\n");
   	}
   	else
   	{
   		printf("Sent : %s\n", buffer);
   	}
   	
    //game logic
    while(1)
    {
    	//receive key strokes
	   	//receive events from server
	   	
	   	//update game structures
	   	
	   	//send events to server
	   	
	   	//print game
   	}
   	
   	
   	//closing socket
	shutdown(sock, 2);
	closesocket(sock);

    
    #if defined (WIN32)
        WSACleanup();
    #endif

	return EXIT_SUCCESS;
}
