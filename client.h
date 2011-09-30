#ifndef DEF_CLIENT_H
#define DEF_CLIENT_H

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	//multi-thread
	#include <pthread.h>
	
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
	
	SOCKET initNetwork();
	
	#define PORT 2300
	
#endif
