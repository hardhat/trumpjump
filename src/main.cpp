#include "main.h"
#include "game.h"
#include "font.h"
#include "sound.h"

Game game;
Sound sound;
Font font;

extern "C" {
int main(int argc,char **argv);
}

int main(int argc,char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	// init window and renderer

	// Init joystick
	SDL_Joystick *joy=SDL_OpenJoystick(0);

	// Init audio

	bool done=false;
	while(!done) {
		// handle events
		SDL_Event event;

		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT) done=true;
			// dispatch to game object.
		}
		// draw screen
		

		// update game state

	}
	SQL_Quit();
	return 0;
}
