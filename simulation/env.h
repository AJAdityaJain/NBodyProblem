#pragma once
#include "../global.h"
#include "body.h"

float randomFloat();

class Env {
public:
	std::vector<Body> bodies;
	int create();
	int approxGaussianGen(int num, int rad);
	int gridGen(int X, int Y);
	int polarGen(int b);
};

