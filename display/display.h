#pragma once
#include "../simulation/env.h"
#include "renderer.h"

class Display {

public:
	Renderer renderer;

	bool init();
	void poll(bool& run, Env& env);
	void render(Env& env);
	void quit();

private:
	bool initWindow();
};

