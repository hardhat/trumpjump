#ifndef GAME_H
#define GAME_H
#include <SDL.h>

class Game
{
public:
	Game();
	~Game();
	
	/// initialize everyting.
	void init();
	/// start a new round.
	void resetGame();
	/// key press
	void handleKey(int key,bool down);
	/// mouse or finger click
	void handleButton(int x,int y,bool down);
	/// mouse or finger drag
	void handleMotion(int x,int y);
	/// draws the screen and presents it
	void draw(SDL_Renderer *renderer);
	/// update the game state, time in 1/1000ths of a second.
	void update(int elapsed);	
private:
	int mode;

	int score;
	int highScore;
};

#endif
