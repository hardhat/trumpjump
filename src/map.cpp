#include <SDL.h>
#include <stdio.h>
#include "map.h"
#include "image.h"
#include "world.h"
#include <iostream>

Map::Map()
{
    // TODO Encapsulate screensize into a singleton / config so we stretch later
    // From global: screensize={640,384};
    w = 640;
    h = 384;
    worldW = w / 32;
    worldH = h / 16;
}

Map::~Map()
{
    delete platformImage;
    delete potatoImage;
    delete meatImage;
    delete babyImage;
    delete moneyImage;
}

void Map::loadImages() {
    // TODO initialize into spritemaps
    platformImage = new Image( World::getRenderer(), "platform.png");
    potatoImage = new Image( World::getRenderer(), "small_potatoes.png");
    meatImage = new Image( World::getRenderer(), "Meatloaf.png");
    babyImage = new Image( World::getRenderer(), "baby.png");
    moneyImage = new Image( World::getRenderer(), "Money.png");
}

void Map::generateObjects() {
}

void Map::init()
{
    // Load assets
    loadImages();
}

void Map::newGame()
{
    printf("Map: New Game Init\n");
}

void Map::draw(SDL_Renderer *renderer)
{
    Image *toDraw;
    // TODO: iterate through game objects
}

void Map::update(int elapsed) { 
    // data structure - this is a case where a linked list(vector?) would work

    // TODO 1. shift horizontally
    // TODO 2. determine if still in display
    // TODO 3. dispose
}

int Map::collide(int x,int y,int w,int h)
{
    return MAP_SKY;
}

int Map::collect(int x,int y,int w,int h)
{

    return 0;
}

