#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include "image.h"

enum MapItems {
    MAP_SKY = 0,
    MAP_BARRIER,
    MAP_REDSTAR,
    MAP_BLUESTAR,
    MAP_WHITESTART,
    MAP_POTATO,
    MAP_MEATLOAF,
    MAP_SIGN,
    MAP_MONEY,
};

class Map
{
    public:
        Map();
        ~Map();

        /// one time load for map resources
        void init();
        /// clear and reset the map
        void newGame();
        /// update the map at a constant speed
        void update(int elapsed);
        /// draw the current map state
        void draw(SDL_Renderer *renderer);
        /// returns the MAP_SKY or MAP_BARRIER, or the item the you'd collect
        int collide(int x,int y,int w,int h);
        /// returns the item
        int collect(int x,int y,int w,int h);
    private:
        int w;
        int h;
        // TODO Create a World object that implements bijection of w/h<->worldW/h
        // TODO Accept with global object
        int worldW;
        int worldH;
        MapItems *map;

        int left;	// in screen pixels, for the map scrollng
        int NUM_ITEMS;
        // TODO Use this signiture for sprite map, not individual instances
        // Image *itemsImage;


        // Maybe use a lookup table that matches with enum value?
        Image *itemPotato;
        Image *itemMeatLoaf;
        Image *itemSign;

        // Platform image; leave as separate as a filler
        Image *platformImage;
};

#endif
