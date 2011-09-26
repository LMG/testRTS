#ifndef DEF_SERVER_H
#define DEF_SERVER_H

	#include <stdio.h>
	#include <stdlib.h>
	
	//multi-thread
	#include <pthread.h>
	void* manageClient(void*);
	
	//network
	#if defined (WIN32)

		#include <winsock2.h>
		typedef int socklen_t;

	#elif defined (linux)

		#include <sys/types.h>
		#include <sys/socket.h>
		#include <netinet/in.h>
		#include <arpa/inet.h>
		#include <unistd.h>

		#define INVALID_SOCKET -1
		#define SOCKET_ERROR -1
		#define closesocket(s) close (s)

		typedef int SOCKET;
		typedef struct sockaddr_in SOCKADDR_IN;
		typedef struct sockaddr SOCKADDR;
		
	#endif
	
	#define PORT 2300
	#define CLIENT_NB 4

#endif
