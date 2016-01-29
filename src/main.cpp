#include "main.h"
#include "game.h"
#include "font.h"
#include "sound.h"
#include "image.h"

Game game;
SDL_Point screensize={640,384};

extern "C" {
int main(int argc,char **argv);
}

int main(int argc,char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	// init window and renderer
	// TODO: query the screen and set the resolution based on the screen size.
	SDL_Window *window=SDL_CreateWindow("Super Trump Jump",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,384,0);
	screensize.x=640;
	screensize.y=384;
	renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

	// Init joystick
	SDL_Joystick *joy=0;
	if(SDL_NumJoysticks()>0) {
		joy=SDL_OpenJoystick(0);
	}
	if(SDL_NumJoysticks()>1) {
		joy=SDL_OpenJoystick(1);
	}

	// Init audio
	Sound::init();

	// Init image loader
	Image::init();

	// Init font loader
	Font::init();

	int elapsed
	bool done=false;
	while(!done) {
		// handle events
		SDL_Event event;

		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT) {
				done=true;
			// dispatch to game object.
	if(SDL_NumJoysticks()>0) {
		SDL_Joystick *joy=SDL_OpenJoystick(0);
	}

	// Init audio
	sound.init();

	// Init image loader
	image.init();

	// Init font loader
	font.init();

	int elapsed
	bool done=false;
	while(!done) {
		// handle events
		SDL_Event event;

		while(SDL_PollEvent(&event)) {
			if(event.type==SDL_QUIT) {
				done=true;
			// dispatch to game object.
			} else if(event.type==SDL_KEYDOWN) {
				if(event.key.keysym.sym==' ') {
					game.handleKey(' ',true);
				}
			} else if(event.type==SDL_KEYUP) {
				if(event.key.keysym.sym==' ') {
					game.handleKey(' ',false);
				}
			} else if(event.type==SDL_MOUSEBUTTONDOWN) {
				int x=event.mouse.x;
				int y=event.mouse.y;
				game.handleButton(x,y,true);
			} else if(event.type==SDL_MOUSEBUTTONUP) {
				int x=event.mouse.x;
				int y=event.mouse.y;
				game.handleButton(x,y,false);
			} else if(event.type==SDL_MOTION) {
				int x=event.motion.x;
				int y=event.motion.y;
				game.handleMotion(x,y);
			}
		}
		// draw screen
		game.draw(renderer);

		// update game state
		game.update(elapsed);
	}
	SQL_Quit();
	return 0;
}
