client : client.c client.h graphics.o game.h
	gcc -o client client.c graphics.o -Wall -g -lpthread -lSDL -lSDL_image 
graphics.o :  graphics.c graphics.h game.h
	gcc -o graphics.o -c graphics.c -lSDL -lSDL_image -Wall -g
server : server.c server.h game.h
	gcc -o server server.c -Wall -g -lpthread
clean :
	rm *.o
	rm *~
mrproper : clean
	rm client server
