#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include "image.h"

enum MapItems {
	MAP_SKY,
	MAP_BARRIER,
	MAP_REDSTAR,
	MAP_BLUESTAR,
	MAP_WHITESTART,
	MAP_POTATO,
	MAP_MEATLOAF,
	MAP_SIGN,
	MAP_MONEY,
};

class Map
{
public:
	Map();
	~Map();

	/// one time load for map resources
	void init();
	/// clear and reset the map
	void newGame();
	/// update the map at a constant speed
	void update(int elapsed);
	/// draw the current map state
	void draw(SDL_Renderer *renderer);
	/// returns the MAP_SKY or MAP_BARRIER, or the item the you'd collect
	int collide(int x,int y,int w,int h);
	/// returns the item
	int collect(int x,int y,int w,int h);
private:
	int w;
	int h;
	int *map;
	int left;	// in screen pixels, for the mpa scrollng
	Image *itemsImage;
	Image *platformImage;
};

#endif
