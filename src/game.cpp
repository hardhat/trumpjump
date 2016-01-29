#include <SDL.h>
#include "game.h"

Game::Game()
{
}

/// Clean up all resources loadded with init.
Game::~Game()
{
}


/// initialize everyting.
void Game::init()
{
	/// load all of the images, and so forth.  Run once.
}

/// start a new round.
void Game::resetGame()
{
}

/// key press
void Game::handleKey(int key,bool down)
{
}

/// mouse or finger click
void Game::handleButton(int x,int y,bool down)
{
}

/// mouse or finger drag
void Game::handleMotion(int x,int y)
{
}

/// draws the screen and presents it
void Game::draw(SDL_Renderer *renderer)
{
}

/// update the game state, time in 1/1000ths of a second.
void Game::update(int elapsed)
{

}
