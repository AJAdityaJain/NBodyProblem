#include "body.h"

Body::Body(float x, float y)
{
		position = vector2d(x, y) + ORIGIN;
		velocity = vector2d(0, 0);
		acceleration = vector2d(0, 0);
		density = 1;

		setMass(40);
}

Body::Body(vector2d pos, vector2d vel)
{
		position = pos + ORIGIN;
		velocity = vel;
		acceleration = vector2d(0, 0);
		density = 1;

		setMass(40);
}

float Body::getRadius() const
{
	return radius;
} 
float Body::getMass()const
{
	return mass;
}

void Body::setRadius(float r)
{
	radius = r;
	mass = r * r * PI*density;
}
void Body::setMass(float m)
{
	mass = m;
	radius = sqrt(m / (density *PI));
}