#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <string>
#include "image.h"

Image::Image(SDL_Renderer *renderer,const char *path)
{
    texture=0;
    w=0;
    h=0;
    cellSize=32;

    //printf("Loading image %s\n",path);
    std::string fullpath=(std::string)"data/"+path;
    texture=IMG_LoadTexture(renderer,fullpath.c_str());
    if(!texture) texture=IMG_LoadTexture(renderer,path);
    if(!texture) {
        FILE *file=fopen(fullpath.c_str(),"r");
        if(file) fclose(file);
        printf("Couldn't load '%s', file %s\n",fullpath.c_str(),file?"exists":"not found.");
        return;
    }
    w=0;
    h=0;
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);
    printf("Image: '%s' is %dx%d\n",path,w,h);
}

Image::~Image()
{
    if(texture) SDL_DestroyTexture(texture);
    texture=0;
    w=0;
    h=0;
}

void Image::init()
{
	IMG_Init(IMG_INIT_PNG);
}

void Image::draw(SDL_Renderer *renderer,int x,int y)
{
    // TODO: needs to scale to world coordinates
    if(!texture) return;
    SDL_Rect rect={x,y,w,h};

    SDL_RenderCopy(renderer,texture, NULL, &rect);
}

void Image::draw(SDL_Renderer *renderer,int x,int y,int w,int h)
{
    // TODO: needs to scale to world coordinates
    if(!texture) return;
    SDL_Rect rect={x,y,w,h};

    SDL_RenderCopy(renderer,texture, NULL, &rect);
}

void Image::setCellSize(int size)
{
    cellSize=size;

}

void Image::draw(SDL_Renderer *renderer,int x,int y,int id)
{

        if(!texture) return;
    SDL_Rect rect={x,y,cellSize,cellSize};
     int tx=id%8;
        int ty=id/8;

       SDL_Rect src={cellSize*tx,ty*cellSize,cellSize,cellSize};


    SDL_RenderCopy(renderer,texture, &src, &rect);
}
