#pragma once
#include "../global.h"
#include <SDL.h>
#include "../simulation/env.h"

class Display {

public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event e;

	bool render(Env& env);
	bool init();
	bool poll(bool& run);
	bool quit();

private:
	float zoom= 1;
	bool initWindow();
	void drawCircle(vector2d centre, float radius);
};

