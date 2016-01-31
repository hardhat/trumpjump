#include <SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include "map.h"
#include "image.h"
#include "world.h"
#include <iostream>
#include <vector>

// returns chance of <eye> over <die> roll
bool roll(int die, int eye);
// a % b with a < 0 is implementation-dependant; a helper to yield euculedean modulo
int reminder(int dividend, int divisor);

// Pre-computed sine table
#define SINE_TABLE_SIZE 58
static float sineTable[] = { 0.01745f, 0.05234f, 0.08716f, 0.12187f, 0.15643f, 0.19081f, 0.22495f, 0.25882f, 0.29237f, 0.32557f, 0.35837f, 0.39073f, 0.42262f, 0.45399f, 0.48481f, 0.51504f, 0.54464f, 0.57358f, 0.60182f, 0.62932f, 0.65606f, 0.68200f, 0.70711f, 0.73135f, 0.75471f, 0.77715f, 0.79864f, 0.81915f, 0.83867f, 0.85717f, 0.87462f, 0.89101f, 0.90631f, 0.92050f, 0.92718f, 0.93358f, 0.93969f, 0.94552f, 0.95106f, 0.95630f, 0.96126f, 0.96593f, 0.97030f, 0.97437f, 0.97815f, 0.98163f, 0.98481f, 0.98769f, 0.99027f, 0.99255f, 0.99452f, 0.99619f, 0.99756f, 0.99863f, 0.99939f, 0.99985f, 0.00000f };

#define CELL_LENGTH 16
#define COL_TILE_DESIRED 1
#define COL_STAR_DESIRED 2
#define COL_BARRIER_MIN 1
#define TRUMP_SPEED 0.7f
#define SINE_SIZE 20
Map::Map()
{
}

Map::~Map()
{
    delete platformImage;
    delete potatoImage;
    delete meatImage;
    delete babyImage;
    delete moneyImage;
    delete signImage;
    delete blueStarImage;
    delete redStarImage;
    delete whiteStarImage;
}

void Map::loadImages() {
    // TODO initialize into spritemaps
    platformImage = new Image( World::getRenderer(), "platform.png");
    potatoImage = new Image( World::getRenderer(), "small_potatoes.png");
    meatImage = new Image( World::getRenderer(), "Meatloaf.png");
    babyImage = new Image( World::getRenderer(), "baby.png");
    moneyImage = new Image( World::getRenderer(), "Money.png");
    signImage = new Image( World::getRenderer(), "signfortrump.png");

    blueStarImage = new Image( World::getRenderer(), "AmericanBlueStar.png");
    redStarImage = new Image( World::getRenderer(), "RedAmericanStar.png");
    whiteStarImage = new Image( World::getRenderer(), "WhiteAmericanStar.png");

}

void Map::init()
{
    // Load assets
    loadImages();

    // Slightly larger than the viewport so we have a leeway.
    cCol = std::ceil(World::getWidth() / CELL_LENGTH) * 1.3;
    // Should be taller than the viewport so you can "fall"
    cRow = std::ceil(World::getHeight() / CELL_LENGTH); // * 1.3;

    // Initialize mapGrid, a representation of Grid
    mapGrid = new MapItem*[cCol];
    animationOffsets= new int*[cCol];

    // Initialize into MAP_SKY
    for (int i = 0; i < cCol; i++) {
        mapGrid[i] = new MapItem[cRow];
        animationOffsets[i] = new int[cRow];
        for (int j = 0; j < cRow; j++) {
            mapGrid[i][j] = MAP_SKY;
            animationOffsets[i][j] = rand() % SINE_TABLE_SIZE;
        }
    }
    
    // Pre-compute SINE table
    // SINE_SIZE

    leftCol = 0;
    rightCol = (World::getWidth() / CELL_LENGTH) - 1; // Could be stretched
    colSpan = rightCol - leftCol;
    CreateMap();
    // printMap();

    // Trump moves at default speed
    spd = TRUMP_SPEED;
    // spd = 0.1f; // TRUMP_SPEED;
}

void Map::CreateMap() {
    for (int i = 1; i < cCol; i++) {
        createColumn(i);
    }
}


void Map::createColumn(int col) {
    // Counting struct
    ColCount scanInfo;
    // Column to be examined.
    int prevColumn = reminder(col-1, cCol);
    // Column to be written, in case we start a Barrier this time.
    //int nextColumn = reminder(col+1, cCol);
    // Current Column to be created.
    int currColumn = reminder(col, cCol);

    // Currently created Tile
    int tileCount = 0;
    int platformCount = 0;

    // Clean up first.
    cleanColumn(col);

    scanColumn(prevColumn, scanInfo);

    // Do the Platforms(MAP_BARRIER) first
    for (int row = 1; row < cRow; row++) {
            }

    for (int row = 1; row < cRow; row++) {
        if (mapGrid[prevColumn][row] == MAP_SKY) {
            if (roll(10, 1) && platformCount < COL_BARRIER_MIN) {
                mapGrid[currColumn][row] = MAP_BARRIER_A;
                platformCount++;
            }
        }
        if (mapGrid[prevColumn][row] == MAP_BARRIER_A) {
            mapGrid[currColumn][row] = MAP_BARRIER_B;
        }
        if (mapGrid[currColumn][row] == MAP_BARRIER_A && roll(6, 5)) {
            mapGrid[currColumn][row] = MAP_BARRIER_A;
            tileCount++;
        }


        if (mapGrid[prevColumn][row] != MAP_SKY) {

            // TODO set this Roll to be configurable
            if (roll(7, 3)) {
                if (mapGrid[prevColumn][row] == MAP_BARRIER_B) {
                    mapGrid[currColumn][row] = MAP_BARRIER_A;
                }
                else {
                    // Not multiple babies
                    if (!mapGrid[prevColumn][row] == MAP_BABY) {
                        mapGrid[currColumn][row] = mapGrid[prevColumn][row];
                    }
                }
                // tileCount++;
            }
        }
    }

    // If this column has not enough tiles, give it another shot.
    for( ;tileCount < COL_TILE_DESIRED; tileCount++) {
        MapItem *newTile;
        int nRow = rand() % cRow;

        // TODO set this Roll to be configurable
        if (roll(7, 5)) {
            newTile = &mapGrid[currColumn][nRow];

            if (*newTile == MAP_SKY) {
                *newTile = MapItem(rand() % ITEM_KIND);

                // Not gonna bother with retroactive barriering.
                if (*newTile == MAP_BARRIER_B) {
                    *newTile = MAP_SKY;
                }
            }
        }
    }


    scanColumn(currColumn, scanInfo);
    int totalStars = scanInfo.count[3] + scanInfo.count[4] + scanInfo.count[5]; 
    // Same thing with Stars
    for( ;totalStars < COL_STAR_DESIRED; totalStars++) {
        MapItem *newTile;
        int nRow = rand() % cRow;

        // TODO set this Roll to be configurable
        if (roll(7, 5)) {
            newTile = &mapGrid[currColumn][nRow];

            if (*newTile == MAP_SKY) {
                *newTile = MapItem(rand() % 3 + 2);

                // Not gonna bother with retroactive barriering.
                if (*newTile == MAP_BARRIER_B) {
                    *newTile = MAP_SKY;
                }
            }
        }
    }

}

void Map::scanColumn(int col, ColCount &result) {
    for (int i = 0; i < ITEM_KIND; i++) {
        result.count[i] = 0;
    }
    for (int row = 0; row < cRow; row++) {
        result.count[mapGrid[col][row]]++;
    }
    result.non_sky = cCol - result.count[MAP_SKY];
}

void Map::cleanColumn(int col) {
    // Column to be written, in case we start a Barrier this time.
    int nextCol = (col + 1) % cCol;

    for (int row = 0; row < cRow; row++) {
        // If BARRIER_A, then clean the next part as well.
        if (mapGrid[col][row] == MAP_BARRIER_A) {
            mapGrid[nextCol][row] = MAP_SKY;
        }
        // If BARRIER_B, leave it alone; we don't want to be cleaning up first half.
        if (mapGrid[col][row] != MAP_BARRIER_B) {
            mapGrid[col][row] = MAP_SKY;
        }
    }
}

void Map::newGame()
{
    printf("Map: New Game Init\n");
}

// Compute where at what screen coordinate the Grid Cell must be drawn.
void Map::gridToScreen(int gridX, int gridY, int &screenX, int &screenY) {
    // Nominal - "original" location of the grid; i.e., without any offset.
    float nominalX, nominalY;
    float circularX;
    // Adjusted - location of the draw after the alignment to current location.
    float adjustedX, adjustedY;
    nominalX = gridX * 16.0f;
    nominalY = gridY * 16.0f;

    circularX = nominalX + cCol * 16.0f;

    // Shift by leftmost Col(This part will need to be nomralized later)
    // i.e., no transforming occurs.
    if (leftCol < rightCol) {
    // if (leftCol < gridX) {
        adjustedX = nominalX - (leftCol * 16.0f);
    }
    // i.e., we're appending some left portion onto right
    else {
        // i.e., we're trying to render a Col that is outside of viewport
        //  So it must be transformed onto next circular position
        if (gridX < leftCol) {
            adjustedX = circularX - (leftCol * 16.0f);
        }
        // i.e., this Column is still using normal measurement
        else {
            adjustedX = nominalX - (leftCol * 16.0f);
        }
    }

    // Shift by remaining left float
    adjustedX = (adjustedX - left) * 1.0f;

    // Shift vertically(TOP should be coming from Jump mechanism)
    adjustedY = nominalY * 1.0f;

    World::worldToScreen(adjustedX, adjustedY, screenX, screenY);
}

// TODO 1. Update Leftmost Col
// TODO 2. Update Rightmost Col
// TODO 3. Every time left > TILE_SIZE, shift once.
void Map::screenToGrid(int &gridX, int &gridY, int screenX, int screenY) {
    float worldX, worldY;
    float targetX, targetY;

    // Translate screen coordinates to world coordinate.
    World::screenToWorld(screenX, screenY, worldX, worldY);

    targetX = worldX;
    targetY = worldY;

    // printf("%f, %f, %d, %d\n", targetX, targetY, gridX, gridY);
    targetX = (targetX + left) / CELL_LENGTH;
    targetY = targetY / CELL_LENGTH;

    gridX = (int) std::floor(targetX) + leftCol;
    gridX = reminder(gridX, cCol);
    gridY = (int) std::floor(targetY);

    // printf("%f, %f, %d, %d\n", targetX, targetY, gridX, gridY);

}


void Map::draw(SDL_Renderer *renderer)
{
    Image *toDraw;
    int screenX, screenY;
    float disposition;

    // TODO from leftCol to rightCol
    for (int x = 0; x < cCol; x++) {
        for (int y = 0; y < cRow; y++) {
            switch (mapGrid[x][y]) {
                // Collidable
                case MAP_BARRIER_A:
                    toDraw = platformImage;
                    break;
                // Collectible
                case MAP_POTATO:
                    toDraw = potatoImage;
                    disposition = sineTable[animationOffsets[x][y]++ % SINE_TABLE_SIZE];
                    break;
                case MAP_MONEY:
                    toDraw = moneyImage;
                    disposition = sineTable[animationOffsets[x][y]++ % SINE_TABLE_SIZE];
                    break;
                case MAP_MEATLOAF:
                    toDraw = meatImage;
                    disposition = sineTable[animationOffsets[x][y]++ % SINE_TABLE_SIZE];
                    break;
                case MAP_BABY:
                    toDraw = babyImage;
                    disposition = sineTable[animationOffsets[x][y]++ % SINE_TABLE_SIZE];
                    break;

                // Animation
                case MAP_SIGN:
                    toDraw = signImage;
                    break; 
                case MAP_WHITESTART:
                    toDraw = whiteStarImage;
                    disposition = sineTable[animationOffsets[x][y]++ % SINE_TABLE_SIZE];
                    break;
                case MAP_REDSTAR:
                    toDraw = redStarImage;
                    disposition = sineTable[animationOffsets[x][y]++ % SINE_TABLE_SIZE];
                    break;
                case MAP_BLUESTAR:
                    toDraw = blueStarImage;
                    disposition = sineTable[animationOffsets[x][y]++ % SINE_TABLE_SIZE];
                    break;

                    // SKY
                default:
                    toDraw = NULL;
                    break;
            }

            gridToScreen(x, y, screenX, screenY);

            //printf("%d, %d\n", screenX, screenY);
            if (toDraw != NULL) {
                toDraw->draw(renderer, screenX, screenY + disposition * 3.0f);
            }
            disposition = 0;
        }
    }
}

int Map::handle(int key, bool down) {
    // Stop.
    if (key == '3') {
        spd = 0;
    }
    // Move
    else if (key == '4') {
        spd = TRUMP_SPEED;
    }

    // Move Up. (This functionality will be exported as a public function after this development)
    if (key == '1') {
    }
}


// TODO Map - incorporate 'elapsed' on update
void Map::update(int elapsed) {
    // 1. Shift horizontally.
    // left += TRUMP_SPEED;
    left += spd;

    if (left > CELL_LENGTH) {
        // Column to be written, in case we start a Barrier this time.
        leftCol = reminder(leftCol+1, cCol);
        // printf("left: %f, leftCol: %d, rightCol: %d, colSpan: %d, cCol: %d\n", left, leftCol, rightCol, colSpan , cCol);
        rightCol = reminder(rightCol+1, cCol);

        createColumn(rightCol);
        left = left - CELL_LENGTH;
    }
}

void Map::testCollide(int x, int y) {
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 18; j++) {
            printf("Collide: %d, %d: %d\n", i, j, collide(i, j, 0, 0));
        }
    }
}

int Map::collide(int x,int y,int w,int h)
{
    int gridX, gridY;
    screenToGrid(gridX, gridY, x, y);

    // printf("collide; :[%d, %d] %d, %d = %d\n", gridX, gridY, x, y, mapGrid[gridX][gridY]);
    return mapGrid[gridX][gridY];
}

int Map::collect(int x,int y,int w,int h)
{
    int gridX, gridY;
    screenToGrid(gridX, gridY, x, y);

    int prevColumn = reminder(gridX-1, cCol);
    // Column to be written, in case we start a Barrier this time.
    int nextColumn = reminder(gridX+1, cCol);
    // Current Column to be created.
    int currColumn = reminder(gridX, cCol);

    MapItem item = mapGrid[currColumn][gridY];

    // MAP_BARRIER Really shouldn't be collectible, but if the user insists, do so correctly.
    if (item == MAP_BARRIER_A) {
        mapGrid[currColumn][gridY] = MAP_SKY;
        mapGrid[nextColumn][gridY] = MAP_SKY;
    }
    else if (item == MAP_BARRIER_B) {
        mapGrid[prevColumn][gridY] = MAP_SKY;
        mapGrid[currColumn][gridY] = MAP_SKY;
    }
    else {
        mapGrid[gridX][gridY] = MAP_SKY;
    }
    // printf("%d\n", item);

    return (int) item;
}

// Console Print
void Map::printMap() {
    printf("cCol: %d, cRow: %d\n", cCol, cRow);
    for (int i = 0; i < cRow; i++) {
        printf("[");
        for (int j = 0; j < cCol; j++) {
            printf(" %d ", mapGrid[j][i]);
        }
        printf("]\n");
    }
}

// Console Print
void Map::printCount(ColCount &c) {
    printf("[");
    for (int i = 0; i < ITEM_KIND; i++) {
        printf(" %d ", c.count[i]);
    }
    printf("]\n");
}

// Helper function: returns true for eye / die.
bool roll(int die, int eye) {
    return std::rand() % die < eye;
}


int reminder(int dividend, int divisor) {
    int mod = dividend % divisor;
    if (mod < 0) {
        return (mod + divisor) % divisor;
    }
    return mod;
}
