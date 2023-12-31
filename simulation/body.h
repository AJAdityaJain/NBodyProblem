#pragma once
#include "../global.h"

class Body {
public:
	vector2d position;
	vector2d velocity;
	vector2d acceleration;
	Body(float x, float y);
	Body(vector2d pos, vector2d vel);
	void setRadius(float r);
	void setMass(float m);
	float getRadius() const;
	float getMass() const;

private:
	float radius;
	float mass;

};