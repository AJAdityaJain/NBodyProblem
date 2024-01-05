#include "env.h"

float randomFloat()
{
	return (float)(rand()) / (float)(RAND_MAX);
}




Env::Env() {
	bodies = std::vector<Body>();
}

void Env::create() {

	galaxyGen(vector2d(500, 500), 200, 600);
	//galaxyGen(vector2d(-500,-1000), 200, 600);
	//gridGen(7, 7);
	//polarGen(40);


}




void Env::gridGen(int X,int Y) {
	float d = 50;
	vector2d size = vector2d(X, Y).mulf(d*0.5f).addf(-d/2);

	for (int x = 0; x < X; x++)
		for (int y = 0; y < Y; y++)
			bodies.push_back(Body((x *d) - size.x, (y * d) - size.y));
}

void Env::polarGen(int b) {


	for (size_t i = 0; i <= TAU * 3; i++) {
		if (randomFloat() > 0.5f) {
		for (size_t r = 0; r < b; r++)
		{
			float theta = (float)i / 3;
			vector2d pos = vector2d(sin(theta), cos(theta)).mulf(r * 50);
			vector2d vel = vector2d(-cos(theta), sin(theta)).mulf((r) * 0.001f);
			bodies.push_back(Body(pos, vel));
		}
	}
}
}

void Env::galaxyGen(vector2d o, int n, int r) {
	float m = 100000;
	Body blackhole = Body(o, vector2d(0, 0));
	//blackhole.velocity.x = signbit(o.x)?0.01f:-0.01f;
	blackhole.density = m*10;
	blackhole.setMass(m);
	bodies.push_back(blackhole);


	for (size_t i = 0; i < n; i++)
	{
		float theta = TAU * i / n;
		float rad = (r* randomFloat()) + blackhole.getRadius()+300;
		Uint8 d = randomFloat() > 0.5f ? -1 : 1;

		vector2d pos = vector2d(sin(theta), cos(theta)).mulf(rad);
		vector2d vel = vector2d(-cos(theta)*d, sin(theta) * d).mulf(sqrtf(G * m / rad));
		bodies.push_back(Body(pos.addvec(o), vel));
	}
}