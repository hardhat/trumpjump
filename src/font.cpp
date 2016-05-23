#include "SDL.h"
#include "SDL_ttf.h"
#include <stdio.h>

#include "font.h"


static TTF_Font *fontFace[3];

Font::Font()
{
}

Font::~Font()
{
    for(int i=0;i<3;i++) {
        if(fontFace[i]) TTF_CloseFont(fontFace[i]);
        fontFace[i]=0;
    }
}

void Font::init()
{
	TTF_Init();
	// Load up all of the fonts we will use.
    // TODO: scale up to the global scale.
#ifdef __APPLE__
    fontFace[FF_HEADLINE]=TTF_OpenFont("vera.ttf",36);
    fontFace[FF_BODY]=TTF_OpenFont("vera.ttf",18);
    fontFace[FF_SMALL]=TTF_OpenFont("vera.ttf",14);
#else
    fontFace[FF_HEADLINE]=TTF_OpenFont("data/vera.ttf",36);
    fontFace[FF_BODY]=TTF_OpenFont("data/vera.ttf",18);
    fontFace[FF_SMALL]=TTF_OpenFont("data/vera.ttf",14);
#endif
}

void Font::extent(int font,const char *message,int &w,int &h)
{
        w=0;
        h=0;

        if(!fontFace[font]) return;
        TTF_SizeText(fontFace[font],message,&w,&h);
}

void Font::draw(SDL_Renderer *renderer,int font,const char *message,int x,int y)
{
        SDL_Surface *surf;
        SDL_Rect rect;
        SDL_Color fg={255,255,255,255};
        if(font==2) fg.b=0;

        if(!fontFace[font]) {
                static int count=0;
                if(count<30)
                        printf("message at %d,%d: '%s'\n",x,y,message);
                count++;
                return;
        }
        surf=TTF_RenderText_Blended(fontFace[font],message,fg);
        rect.x=x;
        rect.y=y;
        rect.w=surf->w;
        rect.h=surf->h;
        //SDL_SetColorKey(surf, SDL_SRCCOLORKEY, 0);
        SDL_Texture *tex=0;
        tex=SDL_CreateTextureFromSurface(renderer,surf);
        SDL_FreeSurface(surf);
        SDL_RenderCopy(renderer,tex,NULL,&rect);
        SDL_DestroyTexture(tex);
}
