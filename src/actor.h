#ifndef ACTOR_H
#define ACTOR_H

#include <SDL.h>
#include "image.h"

enum PowerUp {
	PU_NONE,
	PU_BABY,
	PU_POTATO,
	PU_MEATLOAF,
};

class Actor
{
public:
	void handle(bool down);
	void draw(SDL_Renderer *renderer);
	void update(int elapsed);
private:
	int x,y;
	Image *sprite;
	/// active powerup
	int powerup;
	/// time to live for current powerup, or 0 for infinte in ms.
	int timer;
};

#endif
