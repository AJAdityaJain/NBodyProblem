#pragma once
#include <SDL.h>
#include "../global.h"

class Renderer {
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event e;
	

	bool init();
	void quit();

	void setColor(float r, float g, float b);
	void clear();
	void blit();

	void drawRect(vector2d pos, vector2d size);
	void drawCircle(vector2d centre, float radius);
	void drawOct(vector2d centre, float radius);
	
	
	float zoom = 1;
	vector2d pan = { 0, 0 };
};