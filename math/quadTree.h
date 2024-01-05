#pragma once
#include "../simulation/body.h"
#include <SDL.h>
#include "../display/renderer.h"

class Node
{
public:
	vector2d position;
	vector2d size;
	bool hasChildren ;

	Node* child0 = nullptr;
	Node* child1 = nullptr;
	Node* child2 = nullptr;
	Node* child3 = nullptr;
	
	Body* body;
	int mass; 
	vector2d centerOfMass;

	Node(vector2d pos, vector2d size);
	Node(vector2d size);
	Node(float size);
	Node();
	void addBody(Body* b);
	void print(int i);
	void render(Renderer* rend, int i);
	void simulate(Body* b);
	void clear(bool b);
};