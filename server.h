#ifndef DEF_SERVER_H
#define DEF_SERVER_H

	#include <stdio.h>
	#include <stdlib.h>


	#define PORT 2300
	#define CLIENT_NB 4

	//events
	enum events{ WAITING, MOVE };

	//multi-thread
	#include <pthread.h>
	void* manageClient(void*);//threads function
	//arguments
	struct args {
		int status[4];
		int clientNum;
		int event[4];
		int data1[4];
		int data2[4];
		int data3[4];
		int data4[4];
	};
	void clientConnexions(pthread_t thread[CLIENT_NB], struct args*);//creates threads and waits for connexions
	void closeConnexions(pthread_t thread[CLIENT_NB]);//close connexion

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

#endif
