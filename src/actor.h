#ifndef ACTOR_H
#define ACTOR_H

#include "SDL.h"
#include "image.h"

enum PowerUp {
	PU_NONE,
	PU_BABY,
	PU_POTATO,
	PU_MEATLOAF,
	PU_VOTE,
};

class Map;

#define GRAVITY (9.8f/30.0f)
#define MAXVEL 15.0f
#define MINVEL -9.0f
#define JUMP (-GRAVITY*2)

class Actor
{
public:
	Actor();
	~Actor();
	void init();
	void handle(bool down);
	void draw(SDL_Renderer *renderer);
	void update(int elapsed,Map *map);
	void updateGravity(Map *map);
	void collectedItem(int item);
	int getScore();
	void resetScore();
	float getY() { return y; }
private:
	float x,y;
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
	/// the vertical acceleration
	float ay;
	/// the vertical speed
	float vy;
    /// the points
    int score;
    /// the timer to slow the physics
    int physicsTimer;
};
#endif
