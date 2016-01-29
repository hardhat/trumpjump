#include <SDL.h>
#include <SDL_ttf.h>

#include "font.h"


static TTF_Font *fontFace[3];

Font::Font()
{
}

Font::~Font()
{
}

void Font::init()
{
	TTF_Init();
	// Load up all of the fonts we will use.

}

void Font::extent(int font,const char *message,int &w,int &h)
{

}

void Font::draw(int font,const char *message,int x,int y)
{

}
