#include "display.h"

void Display::poll(bool& run, Env& env) {
	SDL_PollEvent(&renderer.e);
	if (renderer.e.type == SDL_QUIT) run = false;

	if (renderer.e.type == SDL_MOUSEBUTTONDOWN) {
		switch (renderer.e.button.button)
		{
			case SDL_BUTTON_LEFT:
				int mx, my;
				SDL_GetMouseState(&mx, &my);
				//Screen space to world space

				mx -= WINDOW_WIDTH / 2;
				my -= WINDOW_HEIGHT / 2;

				mx /= renderer.zoom;
				my /= renderer.zoom;

				mx -= renderer.pan.x;
				my -= renderer.pan.y;


				env.bodies.push_back(Body(mx-10, my-10));
				env.bodies.push_back(Body(mx-10, my));
				env.bodies.push_back(Body(mx, my-10));
				env.bodies.push_back(Body(mx, my));
				env.bodies.push_back(Body(mx+10, my));
				env.bodies.push_back(Body(mx, my+10));
				env.bodies.push_back(Body(mx+10, my+10));
				env.bodies.push_back(Body(mx-10, my+10));
				env.bodies.push_back(Body(mx+10, my-10));
		}
	}


	if (renderer.e.type == SDL_KEYDOWN) {
		switch (renderer.e.key.keysym.sym) {
		case SDLK_ESCAPE:
			run = false;
			break;
		case SDLK_EQUALS:
			renderer.zoom += 0.2f;
			break;
		case SDLK_MINUS:
			if (renderer.zoom > 0.3f) {
				renderer.zoom -= 0.2f;
			}
			break;

		case SDLK_UP:
			renderer.pan.y += 10;
			break;
		case SDLK_DOWN:
			renderer.pan.y -= 10;
			break;
		case SDLK_LEFT:
			renderer.pan.x += 10;
			break;
		case SDLK_RIGHT:
			renderer.pan.x -= 10;
			break;
		}

	}
}

void Display::render(Env& env) {
	renderer.setColor(0, 0, 0);
	renderer.clear();

	renderer.setColor(1, 1, 1);
	renderer.drawRect(ORIGIN, vector2d(60-FPS));

	float maxr = 1,maxg = 1,maxb = 1;
	//for (auto& body : env.bodies) {
	//	if (body.getMass() != 0) {
	//		maxr = max(maxr, body.getMass());
	//		maxg = max(maxg, body.velocity.magnitudesq());
	//		//maxb
	//	}
	//}


	for (auto& body : env.bodies)
	{
		if (body.getMass() != 0) {
			renderer.setColor(body.getMass()/maxr, body.velocity.magnitudesq()/ maxg, maxb);
			renderer.drawOct(body.position, body.getRadius());
		}
	}

	renderer.blit();
}

bool Display::init() {

	renderer = Renderer();

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	return initWindow();
}

void Display::quit() {
	renderer.quit();
}

bool Display::initWindow() {
	return renderer.init();
}

