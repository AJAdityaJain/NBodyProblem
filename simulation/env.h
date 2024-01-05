#pragma once
#include "../global.h"
#include "body.h"
#include "../math/quadTree.h"

float randomFloat();

class Env {
public:
	std::vector<Body> bodies;

	Env() ;

	void create();
	void gridGen(int X, int Y);
	void polarGen(int b);
	void galaxyGen(vector2d o, int n, int r);
	};

