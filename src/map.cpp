#include <SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include "map.h"
#include "image.h"
#include "world.h"
#include <iostream>
#include <deque>
#include <vector>

// forward declaration of helper functions
bool roll(int die);

// Public routines

// Constructor
Map::Map()
{
}

// Destructor 
Map::~Map()
{
    delete platformImage;
    delete potatoImage;
    delete meatImage;
    delete babyImage;
    delete moneyImage;
}

// Init. Must be called before starting a game.
#define CELL_LENGTH 16.0f
void Map::init()
{/*{{{*/
    // Load assets
    loadImages();

    // Set information from Global config.
    float worldWidth = World::getWidth();
    float worldHeight = World::getHeight();

    cellsRow = std::ceil(worldWidth / CELL_LENGTH) + 2;
    cellsColumn = std::ceil(worldHeight / CELL_LENGTH) * 2;

    rightmostCol = std::ceil(worldWidth / CELL_LENGTH);
    leftmostCol = 0;

    // Initialize the Grid
    mapGrid = new int*[cellsRow];

    for (int i = 0; i < cellsRow; i++) {
        mapGrid[i] = new int[cellsColumn];
        for (int j = 0; j < cellsColumn; j++) {
            mapGrid[i][j] = 0;
        }
    }

    for (int i = 0; i < cellsRow; i++) {
        // TODO Instead come up with an init function.
        // populateColumn(i);
    }

    // mapGrid[10][10] = MAP_BARRIER;
    // mapGrid[12][12] = MAP_BARRIER;
    // objects.push_back(GameObject(MAP_BARRIER, 10 * 16, 10* 16));
    // objects.push_back(GameObject(MAP_BARRIER, 12 * 16, 12* 16));

    // starts off at 0.
    left = 0;/*}}}*/
}

// Draw. Draws the map onto screen.
void Map::draw(SDL_Renderer *renderer)
{/*{{{*/
    // Image to draw
    Image *toDraw;
    // GameObject to iterate through.
    GameObject *obj;
    int screenX, screenY;

    // Iterate through the draw objects and draw.
    std::deque<GameObject>::iterator it = objects.begin();

    while (it != objects.end()) {
        obj = &(*it);
        if (obj->Type == MAP_BARRIER) {
            toDraw = platformImage;
        }
        else if (obj->Type == MAP_POTATO) {
            toDraw = potatoImage;
        }
        else if (obj->Type == MAP_MONEY) {
            toDraw = moneyImage;
        }
        else if (obj->Type == MAP_MEATLOAF) {
            toDraw = meatImage;
        }
        World::worldToScreen(obj->x,obj->y,screenX, screenY);
        toDraw->draw(renderer, screenX, screenY);

        // advance iterator
        it++;
    }
}/*}}}*/

#define TRUMP_SPEED 0.5f
void Map::update(int elapsed) {
    // advance./*{{{*/
    // TODO handle overflow
    left += TRUMP_SPEED;

    // Do we need to create another column?
    if (needsNextColumn()) {
        // Create next column
        leftmostCol++; // TODO should update leftmostcol later?
        rightmostCol++;// TODO make advanceCol() function
        processColumn(rightmostCol);
    }

    // update draw objects; in next iteration, they should be drawn as much as we've advanced.
    GameObject *obj;
    int screenX, screenY;

    // Iterate through the draw objects and update horizontal positional values
    for(std::deque<GameObject>::iterator it = objects.begin(); it != objects.end(); it++) {
        obj = &(*it);
        obj->x = obj->x - TRUMP_SPEED;

        // If object is no longer visible, dispose.
        // TODO inspect
        if (obj->x < -16) {
            objects.pop_front();
            it=objects.begin();
        }
    }
}
/*}}}*/

// Collision detection. x, y as world coordinate.
int Map::collide(int x,int y,int w,int h)
{
    return MAP_SKY;
}

int Map::collect(int x,int y,int w,int h)
{
    return 0;
}


// Helper utility functions on Cell management




// Private routines: Init
void Map::loadImages() {
    platformImage = new Image( World::getRenderer(), "platform.png");/*{{{*/

    // TODO initialize into spritemaps
    potatoImage = new Image( World::getRenderer(), "small_potatoes.png");
    meatImage = new Image( World::getRenderer(), "Meatloaf.png");
    babyImage = new Image( World::getRenderer(), "baby.png");
    moneyImage = new Image( World::getRenderer(), "Money.png");
}/*}}}*/



// Private functions : Map inner logic.

// Populate Column
void Map::populateColumn(int column, MapItem type, int* count, int countSize) {
    int rowIdx;
    // std::cout << "column: " << column << ": "<<countSize << "[";
    // for (int i = 0; i < countSize; i++) {
    //     std::cout << count[i] << ", ";
    // }
    // std::cout << "]" << std::endl;
    for (int i = 0; i < countSize; i++) {
        //if (roll(1)) {
        if (true) {
            rowIdx = count[i];
            if (mapGrid[rowIdx][column] != type) {
            // if (! mapGrid[rowIdx][column] == type ) {
                // fprintf(stdout, "%d\n", rowIdx);
                mapGrid[rowIdx][column] = type;
                objects.push_back(GameObject(type, column * 16, rowIdx * 16));
            }
        }
    }

    if (countSize < 2) {
        rowIdx = rand() % cellsRow;
        // fprintf(stderr, "rowIdx: %d, column: %d\n", rowIdx, column);
        // fprintf(stderr, "mapGrid[rowIdx][column] = %d, type: %d\n", mapGrid[rowIdx][column], type);
        mapGrid[rowIdx][column] = type;
        // fprintf(stderr, "not failed yet 121j\n");
        objects.push_back(GameObject(type, column * 16, rowIdx * 16));
        // fprintf(stderr, "not failed y et\n");
    }
}

// Process a new Column; 
void Map::processColumn(int column) {
    int prevColumn = (column - 1) % cellsColumn;
    int nextColumn = (column + 1) % cellsColumn;
    int currColumn = column % cellsColumn;
    
    int barrierCount, potatoCount, moneyCount, meatCount; 
    int barrierLoc[10], potatoLoc[10], moneyLoc[10], meatLoc[10];

    // scan for barrier
    barrierCount = scanColumn(prevColumn, MAP_BARRIER, barrierLoc, 10);
    potatoCount  = scanColumn(prevColumn, MAP_POTATO, potatoLoc, 10);
    //moneyCount = scanColumn(prevColumn, MAP_MONEY, moneyLoc, 10);
    //meatCount = scanColumn(prevColumn, MAP_MEATLOAF, meatLoc, 10);


    populateColumn(column, MAP_BARRIER, barrierLoc, barrierCount);
    populateColumn(column, MAP_POTATO, potatoLoc, potatoCount);
    //populateColumn(column, MAP_MONEY, moneyLoc, moneyCount);
    //populateColumn(column, MAP_MEATLOAF, meatLoc, meatCount);


    // printf("at column %d, barrier count - %d\n", prevColumn, barrierCount);

    // int rowIdx;
}

// Scan a specific column for a specific MapItem type, and fills the buffer with row index. Returns #.
int Map::scanColumn(int column, int type, int *buffer, int bufSize) {
    int nextIdx = 0;
    for (int row = 0; row < cellsRow; row++) {
        if (mapGrid[row][column] == type) {
            buffer[nextIdx++] = row;
            if (nextIdx > bufSize) {
                return nextIdx;
            }
        }
    }
    return nextIdx;
}

void Map::clearCollulmn(int column) {
    for (int i = 0; i < cellsRow; i++ ) {
        mapGrid[i][column] = 0;
    }
}


void Map::newGame()
{
    printf("Map: New Game Init\n");
}


bool isInteger(float f) {
    return ceil(f) == f && floor(f) == f;
}

// determine if another column needs to be created.
bool Map::needsNextColumn() {
    float l = left + World::getWidth();
    float r = rightmostCol * 16;
    if (l > r) {
        return true;
    }
    else false;
}


// Helper function: returns true for 1 / die.
bool roll(int die) {
    return std::rand() % die == 0;
}

