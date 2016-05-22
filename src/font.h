#ifndef FONT_H
#define FONT_H

#include "SDL.h"

enum FontFace {
	FF_BODY,
	FF_SMALL,
	FF_HEADLINE
};

class Font
{
public:
	Font();
	~Font();
	static void init();
	static void extent(int font,const char *messgae,int &w,int &h);
	static void draw(SDL_Renderer *renderer,int font,const char *message,int x,int y);
};

#endif
