#ifndef DEF_CLIENT_H
#define DEF_CLIENT_H

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
		
	//network
	#if defined (WIN32)

		#include <winsock2.h>
		typedef int socklen_t;

        //we replace the sleep function by the Sleep function which takes microseconds and not seconds (hence the multiplication)
		#define sleep(x) Sleep(1000*(x))

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
	
	//multi-thread
	#include <pthread.h>
	struct threadData {//data sent to the thread
		struct map* map;
		struct flags* flags;
		SOCKET sock;
	};
	
	struct flags {//semaphores and changes flags.
		int modifyingMap;//map being modified right now (need to be reset after modification)
		int mapModified;//map has been modified since last reset of the flag
	};
	
	void* receiveData(void* threadData);//thread function
	
#endif
