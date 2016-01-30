#include <SDL.h>
#include "world.h"
#include "actor.h"

Actor::Actor()
{
    x=128;
    y=160;
}

Actor::~Actor()
{

}

void Actor::init()
{
    sprite=new Image(World::getRenderer(),"Trump.png");
}

void Actor::update(int elapsed)
{

}

void Actor::handle(bool down)
{

}

void Actor::draw(SDL_Renderer *renderer)
{
    if(sprite) {
        sprite->draw(renderer,x,y);
    }
}
