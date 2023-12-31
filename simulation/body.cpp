#include "body.h"

Body::Body(float x, float y)
{
		position = vector2d(x, y);
		velocity = vector2d(0, 0);
		acceleration = vector2d(0, 0);
		setRadius(4);
}

Body::Body(vector2d pos, vector2d vel)
{
		position = pos;
		velocity = vel;
		acceleration = vector2d(0, 0);
		setRadius(4);
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
	mass = r * r * PI;
}
void Body::setMass(float m)
{
	mass = m;
	radius = sqrt(m / PI);
}