//float lastTime = 0, currentTime = 0, deltaTime = 0;
	//lastTime = currentTime;
	//currentTime = SDL_GetTicks();
	//deltaTime = currentTime - lastTime;


#include "main.h"
#include <stdio.h>
#include <time.h>
#include <dos.h>
#include <windows.h>

World::World() {
	env = Env();
	dis = Display();
	sim = Simulator();

	env.create();
}


int main(int argc, char* args[])
{
	World w = World();

	thread rend1(displayThread,&w);
	
	simulationThread(&w);

	rend1.join();
	return 0;
}
int simulationThread(World* w) {

	Sleep(2000);
	while (run) {
		w->sim.update(&w->env);
	}

	return 1;
}

int displayThread(World* w) {
	if (! w->dis.init())return -1;
	while (run) {
		w->dis.render(w->env);
		w->dis.poll(run);
	}
	w->dis.quit();
	return 1;
}