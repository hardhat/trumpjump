#include "world.h"

float World::scale;
float World::top;
float World::left;
float World::width;
float World::height;
SDL_Renderer *World::renderer;

World::World()
{
    //ctor
}

World::~World()
{
    //dtor
}

void World::worldToScreen(float wx,float wy,int &sx,int &sy)
{
    sx=(int)wx;
    sy=(int)wy;
    if(scale!=0) {
        sx=(wx-left)*scale;
        sy=(wy-top)*scale;
    }
}

void World::screenToWorld(int sx,int sy,float &wx,float &wy)
{
    wx=sx;
    wy=sy;
    if(scale!=0) {
        wx=sx/scale+left;
        wy=sy/scale+top;
    }
}
