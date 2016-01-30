#include <SDL.h>

#include "image.h"
#include "font.h"
#include "hud.h"

Hud::Hud()
{

}

Hud::~Hud()
{

}

void Hud::init()
{

}

void Hud::draw(SDL_Renderer *renderer)
{
    Font::draw(renderer, FF_HEADLINE, "Super Trump Jump",0,0);
    Font::draw(renderer, FF_BODY, "Score 0    Money 0    Voter confidence: **OOO",0,38);
}

void Hud::update(int elapsed)
{

}
