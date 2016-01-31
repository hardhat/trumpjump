#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <vector>
#include "image.h"

enum MapItem {
    MAP_SKY = 0,   // 0
    MAP_BARRIER_A, // 1
    MAP_BARRIER_B, // 2 (Not rendered; a placeholder)
    MAP_REDSTAR,   // 3
    MAP_BLUESTAR,  // 4
    MAP_WHITESTART,// 5
    MAP_POTATO,    // 6
    MAP_MEATLOAF,  // 7
    MAP_SIGN,      // 8
    MAP_MONEY,     // 9
    MAP_SIGN_B,    // 10 (Not rendered; a placeholder)
    MAP_BABY,      // 11
};

#define ITEM_KIND 12
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

        // Public debug method; move Trump Up and Down(i.e., move World Down and Up)
        int handle(int key, bool down);

        // Published method; move world forward but Trump stops(Blocked by a block maybe?)
        int stopTrump();

        // Published method; move Trump a bit faster.
        int sprint();

        // Published method; move Trump at normal speed.
        int run();
    private:
        // Load assets
        void loadImages();

        int getGrid(int x,int y);
        void setGrid(int x,int y,int value);

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

        // one-to-one to mapgrid; computes vertical disposition with (0,0) being the highest.
        int **animationOffsets;
        // Pre-computed sine table; use SINE_SIZE constant

        // Offset from the (0, 0) - disposition in X
        float left;
        // Offset from the (0, 0) - disposition in Y
        float top;

        // horizontal speed
        float spd;

        // Leftmost Column of the Grid we're showing.
        int leftCol;
        // Rightmost Column of the Grid we're showing.
        int rightCol;
        // How many Columns does the viewport fit?
        int colSpan;

        // Item images
        Image *potatoImage;
        Image *meatImage;
        Image *babyImage;
        Image *moneyImage;
        Image *signImage;

        // Platform image; leave as separate as a filler
        Image *platformImage;

        // Bouncable images;
        Image *blueStarImage;
        Image *redStarImage;
        Image *whiteStarImage;

        // Debug methods
        void printMap();
        void printCount(ColCount &c);

        void testCollide(int x, int y);
};

#endif
