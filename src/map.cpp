#include <SDL.h>
#include "map.h"
#include "image.h"
#include "world.h"

Map::Map()
{
    // TODO set this to be configurable
    NUM_ITEMS = 5;
    // TODO Encapsulate screensize into a singleton / config so we stretch later
    // From global: screensize={640,384};
    w = 640;
    h = 384;
    worldW = w / 32;
    worldH = h / 16;
}

Map::~Map()
{

}

void Map::init()
{

    // TODO initialize images
    // TODO initialize into spritemaps
    platformImage = new Image( World::getRenderer(), "data/platform.png" );
}

void Map::newGame()
{
    printf("Map: New Game Init\n");
}

void Map::draw(SDL_Renderer *renderer)
{
    platformImage->draw(renderer, 0, 0);
}

void Map::update(int elapsed)
{

}

int Map::collide(int x,int y,int w,int h)
{

    return MAP_SKY;
}

int Map::collect(int x,int y,int w,int h)
{

    return 0;
}

