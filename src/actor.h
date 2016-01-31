#ifndef ACTOR_H
#define ACTOR_H

#include <SDL.h>
#include "image.h"

enum PowerUp {
	PU_NONE,
	PU_BABY,
	PU_POTATO,
	PU_MEATLOAF,
	PU_VOTE,
};

class Actor
{
public:
	Actor();
	~Actor();
	void init();
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
	/// Sprite Animation frame (Four Total)
	int frame;
	/// Timer for Animation
	int frameTimer;
	/// True if tapped on screen/jump buttton pressed.
	bool jump;
};
#endif
