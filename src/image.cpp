#include <SDL.h>
#include <SDL_image.h>

#include "image.h"

Image::Image(const char *path)
{

}

Image::~Image()
{

}

void Image::init()
{
	IMG_Init(IMG_INIT_PNG);
}

void Image::draw(SDL_Renderer *renderer,int x,int y)
{


}

void Image::draw(SDL_Renderer *renderer,int x,int y,int w,int h)
{

}


