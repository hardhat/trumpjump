#ifndef HUD_H
#define HUD_H

#include "SDL.h"

/// Heads up display.
class Hud
{
public:
	Hud();
	~Hud();
	void init();
	void draw(SDL_Renderer *renderer);
	void update(int elapsed,int score);
private:
    int score;
};

#endif
