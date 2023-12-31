#include "env.h"

float randomFloat()
{
	return (float)(rand()) / (float)(rand());
}

float approxGaussian() {
	return exp(-pow(randomFloat()*2,2));
}


int Env::create() {
	bodies = std::vector<Body>();

	//approxGaussianGen(6000,2000);
	polarGen(10);

	return 0;
}

int Env::approxGaussianGen(int num, int rad) {
	vector2d origin = vector2d(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	for (size_t i = 0; i < num; i++)
	{
		float r = approxGaussian() * rad;
		float theta = randomFloat() * TAU;
		vector2d pos = vector2d(sin(theta), cos(theta)).mulf(r);
		vector2d vel = vector2d( -cos(theta), sin(theta)).mulf(0.07f*(rad-r)/rad);
		bodies.push_back(Body(pos + origin, vel));

	}
	return 1;

}

int Env::gridGen(int X,int Y) {

	for (int x = 0; x < X; x++)
	{
		for (int y = 0; y < Y; y++)
		{
			bodies.push_back(Body(200.0f + (x *50), 50.0f + (y * 50)));
		}
	}
	return 1;
}

int Env::polarGen(int b) {

	vector2d origin = vector2d(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	for (size_t r = 0; r < b; r++)
	{
		for (size_t i = 0; i < r * TAU; i++)
		{
			float theta = (float)i / r;
			vector2d pos = vector2d(sin(theta), cos(theta)).mulf(r * 50);
			vector2d vel = vector2d(-cos(theta), sin(theta)).mulf(0.005f * r);
			bodies.push_back(Body(pos + origin, vel));
		}
	}
	return 1;

}