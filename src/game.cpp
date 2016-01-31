#include <SDL.h>
#include "game.h"
#include "actor.h"
#include "world.h"
#include "map.h"
#include "hud.h"
#include "sound.h"
#include "font.h"

Game::Game()
{
    mode=MODE_MENU;
    score=0;
    // TODO: load the highScore from the file system.
    highScore=0;
    title=NULL;
}

/// Clean up all resources loadded with init.
Game::~Game()
{
    // TODO: save the highScore to the file system.
}


/// initialize everyting.
void Game::init(SDL_Renderer *renderer)
{
	/// load all of the images, and so forth.  Run once.
    if(!title) title=new Image(World::getRenderer(),"title.png");

    // Prepare into first initial state.
    resetGame();
}

/// start a new round.
void Game::resetGame()
{
    mode=MODE_MENU;
    if(!hud) {
        hud=new Hud();
        hud->init();
    }
    if(!hero) {
        hero=new Actor();
        hero->init();
    }
    if(!map) {
        map=new Map();
        map->init();
    }
    Sound::playSong(0);
    Sound::playSfx(SFX_START);
}

/// key press
void Game::handleKey(int key,bool down)
{
    if(mode==MODE_MENU) {
        mode=MODE_PLAY;
    } else {
        hero->handle(down);
        if(down) Sound::playSfx(SFX_JUMP);
    }
}

/// mouse or finger click
void Game::handleButton(int x,int y,bool down)
{
    if(mode==MODE_MENU) {
        mode=MODE_PLAY;
    } else {
        hero->handle(down);
        if(down) Sound::playSfx(SFX_JUMP);
    }
}

/// mouse or finger drag
void Game::handleMotion(int x,int y)
{
}

/// draws the screen and presents it
void Game::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer,0x00,0xbf,0xbf,0xff);
    SDL_RenderClear(renderer);

    if(mode==MODE_MENU) {
        title->draw(renderer,0,0);
        SDL_RenderPresent(renderer);
        return;
    }

    // main level
    map->draw(renderer);
    hero->draw(renderer);
    hud->draw(renderer);
    SDL_RenderPresent(renderer);
}

/// update the game state, time in 1/1000ths of a second.
void Game::update(int elapsed)
{
    map->update(elapsed);
    hero->update(elapsed);
    hud->update(elapsed);
}
