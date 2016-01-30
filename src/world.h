#ifndef WORLD_H
#define WORLD_H

#include <SDL.h>

class World
{
    public:
        World();
        ~World();
        static void setScale(float val) { scale = val; }
        static void setLeftTop(float valX,float valY) { left = valX, top = valY; }
        static void setWidthHeight(float valW,float valH) { width = valW, height = valH; }
        static float getScale() { return scale; }
        static float getTop() { return top; }
        static float getLeft() { return left; }
        static float getWidth() { return width; }
        static float getHeight() { return height; }
        static void worldToScreen(float wx,float wy,int &sx,int &sy);
        static void screenToWorld(int sx,int sy,float &wx,float &wy);
        static SDL_Renderer *getRenderer() { return renderer; }
        static void setRenderer(SDL_Renderer *theRenderer) { renderer = theRenderer; }
    protected:
    private:
        static float scale;
        static float top;
        static float left;
        /// Width in world coordinates
        static float width;
        /// Height in world coordinates
        static float height;
        static SDL_Renderer *renderer;
};

#endif // WORLD_H
