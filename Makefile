main : graphics.o main.c
	gcc -o main main.c graphics.o -Wall -lSDL -lSDL_image
graphics.o :  graphics.c graphics.h
	gcc -o graphics.o -c graphics.c -lSDL -lSDL_image -Wall
