#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "game.h"
#include "font.h"
#include "sound.h"
#include "image.h"
#include "world.h"

Game game;

extern "C" {
int main(int argc,char **argv);
}

int main(int argc,char **argv)
{
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	// init window and renderer
	// TODO: query the screen and set the resolution based on the screen size.
	SDL_Window *window=SDL_CreateWindow("Super Trump Jump",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,384,0);
	World::setWidthHeight(640,384);
	SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    World::setRenderer(renderer);
    World::setScale(0.0f);


	// Init joystick
	SDL_Joystick *joy=0;
	if(SDL_NumJoysticks()>0) {
		joy=SDL_JoystickOpen(0);
	}
	if(SDL_NumJoysticks()>1) {
		joy=SDL_JoystickOpen(1);
	}

	// Init audio
	Sound::init();

	// Init image loader
	Image::init();

	// Init font loader
	Font::init();

	srand(time(NULL));

	game.init(renderer);

	// TODO calculatre this with acutal time in ms.
	int elapsed=16;
	bool done=false;
	unsigned int old=SDL_GetTicks();
	while(!done) {
		// handle events
		SDL_Event event;

		while(SDL_PollEvent(&event)) {
			// dispatch to game object.
			if(event.type==SDL_QUIT) {
				done=true;
            } else if(event.type==SDL_KEYUP) {
                if(event.key.keysym.sym==27) done=true;
				if(event.key.keysym.sym==' ') {
					game.handleKey(' ',false);
				}
			} else if(event.type==SDL_KEYDOWN) {
				if(event.key.keysym.sym==' ') {
					game.handleKey(' ',true);
				}
			} else if(event.type==SDL_MOUSEBUTTONDOWN) {
				int x=event.button.x;
				int y=event.button.y;
				game.handleButton(x,y,true);
			} else if(event.type==SDL_MOUSEBUTTONUP) {
				int x=event.button.x;
				int y=event.button.y;
				game.handleButton(x,y,false);
			} else if(event.type==SDL_MOUSEMOTION) {
				int x=event.motion.x;
				int y=event.motion.y;
				game.handleMotion(x,y);
			}
		}
		// draw screen
		game.draw(renderer);

        unsigned int now=SDL_GetTicks();
        elapsed=now-old;
        if(elapsed>1000) elapsed=16;
		if(elapsed>0) game.update(elapsed);

        now=SDL_GetTicks();
        int delay=(old+16)-now;
        if(delay>0) SDL_Delay(delay);
		// update game state
        old=now;
	}
	SDL_Quit();
	return 0;
}
