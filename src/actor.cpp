#include <SDL.h>
#include "world.h"
#include "actor.h"
#include "map.h"
#include "font.h"
#include "sound.h"

Actor::Actor()
{
    x=128;
    y=160;
    jump=false;
    // Animation state
    frame=0;
    frameTimer=150;
    // Power up
    powerup=0;
    timer=0;
    // physics
    ay=0;
    vy=0;
}

Actor::~Actor()
{

}

void Actor::init()

{
    sprite=new Image(World::getRenderer(),"Trump.png");

    sprite->setCellSize(32);
}

void Actor::update(int elapsed, Map *map)
{
    // Update the animation frame
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
            if(frame==4){
                frame=0;
            }
            frameTimer+=150;
        }
    }
    // Apply the physics.
    printf("Physics!!! %d\n",elapsed);
    while(elapsed>0) {
        elapsed-=16;
        updateGravity(map);
    }

}

void Actor::updateGravity(Map *map)
{
        if( ay!=0) {
                printf("y=%.2f; vy=%.2f; ay=%.2f\n",y,vy,ay);
        }
        vy=vy+ay;
        vy=vy+GRAVITY;   // earth gravity is 9.8 m/s^2, or whatever it works out to in your units.
        // apply terminal velocity
        if( vy<MINVEL) {
                vy=MINVEL;
                ay=0;  // hit minimum negative velocity so stop jumping.
        }
        if( vy>MAXVEL) {
                vy=MAXVEL;
                ay=0;  // hit maximum velocity so stop jumping.
        }
        // propose new position, and test for collision:
        float newy=y+vy;
        int i;
        for( i=0; i<8; i++) {
                if( !map->collide(x, newy, 32, 32 ) ) break; // a safe place to move the item to.
                // we don't want to be inside the object, so guess we can move half the distance.
                vy/=2.0f;
                newy=y+vy;
        }
        if( i==8) {
                newy=y; // we can't find a place closer to the ground/ceiling so we need to stop moving.
                vy=0;
                ay=0;
        }
        y=newy; // our new vertical position with gravity and jumping factored in!
}

void Actor::handle(bool down)
{
    ay=down?JUMP:0;
    printf("Jump ay=%.2f\n",ay);
    if(down && !jump) Sound::playSfx(SFX_JUMP);

    jump=down;
}

void Actor::draw(SDL_Renderer *renderer)
{
    if(sprite) {
        sprite->draw(renderer,x,y,frame);
    }
    if (jump==true){Font::draw(renderer, FF_BODY,"Currently Jumping",0,350);}
}
