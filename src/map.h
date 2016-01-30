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
        // Load assets
        void loadImages();

        // apply gravity
        void updateGravity();

        // Generate map
        void generateObjects();

        // NOTE: draw in a buffer? as in to prepare?
        //  May not be necessary; draw() will only have to draw the current area.
        // void drawBlock();
        int w;
        int h;
        // TODO Create a World object that implements bijection of w/h<->worldW/h
        // TODO Accept with global object
        int worldW;
        int worldH;
        MapItems **map;

        int left;	// in screen pixels, for the map scrollng
        // TODO Use this signiture for sprite map, not individual instances
        // Image *itemsImage;

        // position
        float px, py;
        // velocity
        float vx, vy; // vx is move-to-right; always constant.
        // accelleration;
        float ax, ay; 

        // Maybe use a lookup table that matches with enum value?
        Image *potatoImage;
        Image *meatImage;
        Image *babyImage;
        Image *moneyImage;

        // Platform image; leave as separate as a filler
        Image *platformImage;
};

#endif
