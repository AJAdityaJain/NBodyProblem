#include "display.h"

bool Display::poll(bool& run) {
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT) run = false;
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_ESCAPE:
			run = false;
			break;
		case SDLK_EQUALS:
			zoom+=0.2f;
			break;
		case SDLK_MINUS:
			if (zoom > 0.3f) {
				zoom -= 0.2f;
			}
			break;

		}
	}
	return true;
}

bool Display::render(Env& env) {
	SDL_SetRenderDrawColor(renderer, 5, 0, 0, 0);
	SDL_RenderClear(renderer);
	vector2d origin = vector2d(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	//cout << env.bodies[0].position.y-env.bodies[1].position.y << endl;

	for (auto& body : env.bodies)
	{
		if (body.getRadius() != 0) {
			float v = body.getRadius()/30;
			float r, g, b;
			
			if (v < (0.5)) {
				r = 2 * (v);
				g = 2 * (v);
				b = 1;
			}
			else if (v >= (0.5)) {
				b = 1 + 2 * (0.5 - v);
				g = 1 + 2 * (0.5 - v);
				r = 1;
			}

			SDL_SetRenderDrawColor(renderer, r*255, g*255, b*255, 255);
			drawCircle((body.position-origin).mulf(zoom)+origin, body.getRadius()*zoom);
		}
	}

	SDL_RenderPresent(renderer);
	return true;
}

bool Display::init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	return initWindow();
}

bool Display::quit() {
	SDL_DestroyWindow(window);
	SDL_Quit();
	return true;
}

bool Display::initWindow() {
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
	if (window == NULL) { printf("Window could not be created! SDL_Error: %s\n", SDL_GetError()); return false; }

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) { printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError()); return false; }

	return true;
}

void Display::drawCircle(vector2d centre, float radius)
{
	const int32_t diameter = ceil(radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centre.x + x, centre.y - y);
		SDL_RenderDrawPoint(renderer, centre.x + x, centre.y + y);
		SDL_RenderDrawPoint(renderer, centre.x - x, centre.y - y);
		SDL_RenderDrawPoint(renderer, centre.x - x, centre.y + y);
		SDL_RenderDrawPoint(renderer, centre.x + y, centre.y - x);
		SDL_RenderDrawPoint(renderer, centre.x + y, centre.y + x);
		SDL_RenderDrawPoint(renderer, centre.x - y, centre.y - x);
		SDL_RenderDrawPoint(renderer, centre.x - y, centre.y + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}