#include <SDL.h>

#include "image.h"
#include "font.h"
#include "hud.h"

Hud::Hud()
{
    score=0;
}

Hud::~Hud()
{

}

void Hud::init()
{
    score=0;
}

void Hud::draw(SDL_Renderer *renderer)
{
    Font::draw(renderer, FF_HEADLINE, "Super Trump Jump",0,0);
    char buf[256];
    sprintf(buf,"Popularity %d voters",score);
    Font::draw(renderer, FF_BODY, buf ,0,38);
}

void Hud::update(int elapsed,int newScore)
{
    score=newScore;
}
