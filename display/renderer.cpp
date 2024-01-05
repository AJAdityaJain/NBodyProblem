#include "Renderer.h"

bool Renderer::init() {
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
	if (window == NULL) { printf("Window could not be created! SDL_Error: %s\n", SDL_GetError()); return false; }

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) { printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError()); return false; }

	return true;
}

void Renderer::quit() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Renderer::setColor(float r, float g, float b)
{
	SDL_SetRenderDrawColor(renderer, r*255, g*255, b*255, 255);
}

void Renderer::clear() {
	SDL_RenderClear(renderer);
}

void Renderer::blit() {
	SDL_RenderPresent(renderer);
}

void Renderer::drawRect(vector2d pos, vector2d size)
{
	pos = (pos - ORIGIN+pan).mulf(zoom) + ORIGIN;
	size = size.mulf(zoom);

	SDL_Rect rect{
		pos.x,
		pos.y,
		size.x,
		size.y
	};
	
	SDL_RenderFillRect(renderer, &rect);
}

void Renderer::drawCircle(vector2d centre, float radius)
{
	centre = (centre - ORIGIN + pan).mulf(zoom) + ORIGIN;
	radius *= zoom;


	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, centre.x + dx, centre.y + dy);
			}
		}
	}
}

void Renderer::drawOct(vector2d centre, float radius)
{
	centre = (centre - ORIGIN + pan).mulf(zoom) + ORIGIN;
	radius *= zoom;
	float dg = radius * 0.70710678118f;


	SDL_Rect rect{
		centre.x-dg,
		centre.y - dg,
		dg*2,
		dg*2,
	};

	SDL_Rect rect2{
		centre.x - radius,
		centre.y - dg/2,
		radius*2,
		dg,
	};
	SDL_Rect rect3{
		centre.x - dg/2,
		centre.y - radius,
		dg,
		radius*2,
	};

	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderFillRect(renderer, &rect2);
	SDL_RenderFillRect(renderer, &rect3);
}
/* {

	centre = (centre - origin+pan).mulf(zoom) + origin;
	radius *= zoom;

	const int32_t diameter = ceil(radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
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
}*/