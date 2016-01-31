#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <vector>
#include "image.h"

enum MapItem {
    MAP_SKY = 0,   // 0
    MAP_BARRIER_A, // 1 
    MAP_BARRIER_B, // 2 
    MAP_REDSTAR,   // 3
    MAP_BLUESTAR,  // 4
    MAP_WHITESTART,// 5
    MAP_POTATO,    // 6
    MAP_MEATLOAF,  // 7
    MAP_SIGN,      // 8
    MAP_MONEY,     // 9
};

#define ITEM_KIND 10
typedef struct ColCount {
    int count[ITEM_KIND];
    int non_sky;
} ColCount;


struct GameObject {
    MapItem Type;
    float   x;
    float   y;
    int     row;
    int     col;
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

        // Converter function from Grid coordinates and screen coordinates, back and forth.
        void gridToScreen(int gridX, int gridY, int &screenX, int &screenY);
        void screenToGrid(int &gridX, int &gridY, int screenX, int screenY);

        // Generate map at Init.
        void CreateMap();

        // Create a column, based on previous column
        void createColumn(int col);

        // Clean a Column.
        void cleanColumn(int col);


        // Scan a column and count the number of each MapItem cells
        void scanColumn(int col, ColCount &count);

        //
        void shiftColumn();

        // # of Cells in a Row, and a Column.
        int cRow, cCol;

        // the Grid of MapItem. Access by [X][Y] coordinate
        MapItem **mapGrid;

        // Offset from the start.
        float left;
        int leftCol;
        int rightCol;

        // Item images
        Image *potatoImage;
        Image *meatImage;
        Image *babyImage;
        Image *moneyImage;

        // Platform image; leave as separate as a filler
        Image *platformImage;


        // Debug methods
        void printMap();
        void printCount(ColCount &c);

        void testCollide(int x, int y);
};

#endif
