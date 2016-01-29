#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>

class Image {
public:
	Image(const char *path);
	~Image();
	/// call once per program run
	static init();
	/// draw at the global scale
	void draw(SDL_Renderer *renderer,int x,int y);
	/// draw stretched to the requested size in pixel coordinates
	void draw(SDL_Renderer *renderer,int x,int y,int w,int h);
	/// draw cell at the global scale, id in row first order
	void draw(SDL_Renderer *renderer,int x,int y,int id);
	/// set cell size -- cells have to be square
	void setCellSize(int size);
	/// image width in pixels
	int w;
	/// image height in pixels
	int h;
	/// the renderable texture
	SDL_Texture *texture;
private:
	int cellSize;
};

#endif
