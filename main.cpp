

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
		//Sleep(1);
		w->sim.update(&w->env);
	}
	return 1;
}

int displayThread(World* w) {
	float lastTime = 0, currentTime = 0;

	if (! w->dis.init())return -1;
	while (run) {
		lastTime = currentTime;
		currentTime = SDL_GetTicks();
		FPS =  1000/(currentTime - lastTime);

		w->dis.render(w->env);
		w->dis.poll(run, w->env);
	}
	w->dis.quit();
	return 1;
}