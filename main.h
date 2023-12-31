#pragma once
#include "global.h"
#include <thread>
#include "simulation/env.h"
#include "simulation/simulator.h"
#include "display/display.h"


using namespace std;

class World {
public:
	Env env;
	Display dis;
	Simulator sim;

	World();
};

bool run = true;

int displayThread(World* w);
int simulationThread(World* w);