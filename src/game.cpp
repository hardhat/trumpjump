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
    }
    hero->init();
    hero->resetScore();
    if(!map) {
        map=new Map();
        map->init();
    }
    map->newGame();
    Sound::playSong(0);
    Sound::playSfx(SFX_START);
}

/// key press
void Game::handleKey(int key,bool down)
{
    if(mode==MODE_MENU) {
        mode=MODE_PLAY;
    } else if(mode==MODE_LOSE) {
        if(down==false && loseTimer==0) resetGame();
    } else {
        hero->handle(down);
    }
}

/// mouse or finger click
void Game::handleButton(int x,int y,bool down)
{
    if(mode==MODE_MENU) {
        mode=MODE_PLAY;
    } else if(mode==MODE_LOSE) {
        if(down==false && loseTimer==0) resetGame();
    } else {
        hero->handle(down);
        map->collide(x, y, 0, 0);
        map->collect(x, y, 0, 0);
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
    if(mode==MODE_LOSE) {
        int cw=0,ch=0,cx,cy;
        Font::extent(FF_HEADLINE,"Game Over",cw,ch);
        cy=(World::getHeight()-ch)/2;
        cx=(World::getWidth()-cw)/2;
        Font::draw(renderer,FF_HEADLINE,"Game Over",cx,cy);
        if(loseTimer==0) {
            cy+=ch+3;
            Font::extent(FF_BODY,"Tap to Play Again",cw,ch);
            cx=(World::getWidth()-cw)/2;
            Font::draw(renderer,FF_BODY,"Tap to Play Again",cx,cy);
        }
    }

    SDL_RenderPresent(renderer);
}

/// update the game state, time in 1/1000ths of a second.
void Game::update(int elapsed)
{
    if(mode==MODE_PLAY) {
        map->update(elapsed);
        hero->update(elapsed,map);
        score=hero->getScore();
        hud->update(elapsed,score);
        if(hero->getY()>World::getHeight()) {
            mode=MODE_LOSE;
            loseTimer=2000;
            Sound::playSfx(SFX_START);
        }
    } else if(mode==MODE_LOSE) {
        loseTimer-=elapsed;
        if(loseTimer<0) loseTimer=0;
    }
}
