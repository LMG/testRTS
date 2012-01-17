#ifndef DEF_SERVER_H
#define DEF_SERVER_H

	#include <stdio.h>
	#include <stdlib.h>


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
	
	#define PORT 2300
	#define CLIENT_NB 1

	//game and threads arguments structures
	
	//we define SDL_Rect as this is the only structure from SDL we need. (and we don't want to include whole SDL for server)
	typedef struct {
		int x;
		int y;
	}SDL_Rect;
	
	struct flags {//semaphores and changes flags.
		int modifyingMap;//map being modified right now (need to be reset after modification)
		int mapModified;//map has been modified since last reset of the flag
	};
	
	struct threadData {//data sent to the threads
		struct map* map;
		int status;
		int id;
		struct flags* flags;
		SOCKET sock;
	};
	
	//events
	enum events{ WAITING, MOVE };

	//multi-thread
	#include <pthread.h>
	void* manageClient(void*);//threads function
	void clientConnexions(pthread_t thread[CLIENT_NB], struct threadData threadDataArray[CLIENT_NB]);//creates threads and waits for connexions
	void closeConnexions(pthread_t thread[CLIENT_NB]);//close connexion

#endif
