#include <SDL.h>
#include "world.h"
#include "actor.h"
#include "font.h"

Actor::Actor()
{
    x=128;
    y=160;
    //To Do Later = Fix this Bool
    jump=false;

    frame=0;

    frameTimer=150;

    timer=0;
}

Actor::~Actor()
{

}

void Actor::init()

{
    sprite=new Image(World::getRenderer(),"Trump.png");

    sprite->setCellSize(32);
}
void Actor::update(int elapsed)
{
    if (jump==true){
        frame=8;
    }else{
        frameTimer-=elapsed;
        if (frameTimer<=0){
            if (frame==8){
                frame=0;
            }else{
                frame++;
            }
            if(frame==5){
                frame=0;
            }
            frameTimer+=150;
        }
    }
}


void Actor::handle(bool down)
{
jump=down;
}

void Actor::draw(SDL_Renderer *renderer)
{
    if(sprite) {
        sprite->draw(renderer,x,y,frame);
    }
    if (jump==true){Font::draw(renderer, FF_BODY,"Currently Jumping",0,350);}
}
