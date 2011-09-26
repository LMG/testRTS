main : graphics.o main.c
	gcc -o main main.c graphics.o -Wall -lSDL -lSDL_image -g
graphics.o :  graphics.c graphics.h
	gcc -o graphics.o -c graphics.c -lSDL -lSDL_image -Wall -g
server : server.c server.h
	gcc -o server server.c -Wall -g -lpthread
client : client.c client.h
	gcc -o client client.c -Wall -g -lpthread
