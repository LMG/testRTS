#ifndef DEF_GAME_H
#define DEF_GAME_H
	
	//constants and stuff to share between client and server
	#define TILE_HEIGHT 25
	#define TILE_WIDTH 48

	#define NB_TILES_TYPES 10
	#define NB_ENTITIES 1
	
	//game structures
	struct entitie {
		int id;
		int x;
		int y;
		struct entitie* next;
	};

	struct tile {
		int id;
		struct entitie* entitie;
	};
	
	struct map {
		SDL_Rect origin;
		int sizeX;
		int sizeY;
		struct tile **tile;
	};
	
	//network stuff
	#define BUFFER_SIZE 20
#endif
