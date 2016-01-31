#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <vector>
#include <deque>
#include "image.h"

enum MapItem {
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

struct GameObject {
    MapItem Type;
    float   x; // coordinate in world
    float   y; // coordinate in world
    int     col; // Cell column, not used yet
    int     row; // Cell row, not used yet
    GameObject(MapItem t, float x, float y) : Type(t), x(x), y(y) {}
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
        /// draw the current map state
        void draw(SDL_Renderer *renderer);
        /// update the map at a constant speed
        void update(int elapsed);
        /// returns the MAP_SKY or MAP_BARRIER, or the item the you'd collect
        int collide(int x,int y,int w,int h);
        /// returns the item
        int collect(int x,int y,int w,int h);
    private:
        // Load assets
        void loadImages();

        // Generate Column; entry point
        void processColumn(int column);
        // Fills the column with Type
        void populateColumn(int column, MapItem type, int* count, int countSize);

        void clearCollulmn(int column);



        // grid information
        int cellsRow;
        int cellsColumn;
        int **mapGrid;

        // Bookkeeper
        float left;
        int rightmostCol;
        int leftmostCol;

        bool needsNextColumn();
        // Scan a specific column for a specific MapItem type, and fills the buffer with row index. Returns #.
        int scanColumn(int column, int type, int *buffer, int bufSize);

        // std::vector<GameObject> objects;
        std::deque<GameObject> objects;

        // int left;	// in screen pixels, for the map scrollng
        // TODO Use this signiture for sprite map, not individual instances
        // Image *itemsImage;

        // Maybe use a lookup table that matches with enum value?
        Image *potatoImage;
        Image *meatImage;
        Image *babyImage;
        Image *moneyImage;

        // Platform image; leave as separate as a filler
        Image *platformImage;
};

#endif
