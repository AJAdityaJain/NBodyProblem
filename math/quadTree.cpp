#include "quadTree.h"


Node::Node(vector2d pos, vector2d size) {
	this->position = pos;
	this->size = size;
	this->mass = 0;
	this->hasChildren = false;

	this->child0 = nullptr;
	this->child1 = nullptr;
	this->child2 = nullptr;
	this->child3 = nullptr;
	this->body = nullptr;
	this->centerOfMass = vector2d();

}
Node::Node(vector2d size) {
	this->position = ORIGIN - size.mulf(0.5f);
	this->size = size;
	this->mass = 0;
	this->hasChildren = false;

	this->child0 = nullptr;
	this->child1 = nullptr;
	this->child2 = nullptr;
	this->child3 = nullptr;
	this->body = nullptr;
	this->centerOfMass = vector2d();

}
Node::Node(float size) {

	this->position = ORIGIN - vector2d(size*0.5f);
	this->size = size;
	this->mass = 0;
	this->hasChildren = false;

	this->child0 = nullptr;
	this->child1 = nullptr;
	this->child2 = nullptr;
	this->child3 = nullptr;
	this->body = nullptr;
	this->centerOfMass = vector2d();

}

Node::Node() {

	this->size = vector2d(0, 0);
	this->position = ORIGIN - size.mulf(0.5f);
	this->mass = 0;
	this->hasChildren = false;

	this->child0 = nullptr;
	this->child1 = nullptr;
	this->child2 = nullptr;
	this->child3 = nullptr;
	this->body = nullptr;
	this->centerOfMass = vector2d();

}

void Node::addBody(Body* body) {
	if(body->position.x > position.x + size.x || body->position.x < position.x || body->position.y > position.y + size.y || body->position.y < position.y) {
		cout << "\033[1;31m \aOUT OF BOUNDS\033[0m" << endl;
		body->setMass(0);
		return;
	}
	if (!hasChildren) {
		if (this->body == nullptr) {
			this->body = body;
			this->mass = body->getMass();
			this->centerOfMass = body->position;
		}
		else {
			vector2d centre = this->position + this->size.divf(2);
			child0 = new Node(position, this->size.divf(2));
			child1 = new Node(vector2d(centre.x, position.y), this->size.divf(2));
			child2 = new Node(vector2d(position.x, centre.y), this->size.divf(2));
			child3 = new Node(centre, this->size.divf(2));
			this->hasChildren = true;

			Body* body2 = this->body;
			this->body = nullptr;
			this->mass = 0;
			this->centerOfMass = vector2d();

			addBody(body2);
			addBody(body);
		}
	}
	else {

		vector2d centre = this->position + this->size.divf(2);

		if (body->position.x <= centre.x && body->position.y <= centre.y) {
			child0->addBody(body);
		}
		else if (body->position.x >= centre.x && body->position.y <= centre.y) {
			child1->addBody(body);
		}
		else if (body->position.x <= centre.x && body->position.y >= centre.y) {
			child2->addBody(body);
		}
		else if (body->position.x >= centre.x && body->position.y >= centre.y) {
			child3->addBody(body);
		}

		this->mass = child0->mass + child1->mass + child2->mass + child3->mass;
		this->centerOfMass = child0->centerOfMass.mulf(child0->mass) + child1->centerOfMass.mulf(child1->mass) + child2->centerOfMass.mulf(child2->mass) + child3->centerOfMass.mulf(child3->mass);
		this->centerOfMass = this->centerOfMass.divf(this->mass);
	}
}

void Node::print(int i) {
	for (size_t t = 0; t <= i ; t++)
	{
		cout << "....";
	}
	cout << " " << mass << "        ";
	if (mass != 0) {
		cout << "@x:" << centerOfMass.x << " y:" << centerOfMass.y;
	}
	cout << endl;

	if (child0 != nullptr)
		child0->print(i + 1);
	if (child1 != nullptr) 	
		child1->print(i + 1);
	if (child2 != nullptr)
		child2->print(i + 1);
	if (child3 != nullptr)
		child3->print(i + 1);
}

void Node::render(Renderer* rend, int i) {
		rend->setColor(1, 1, 1);
		rend->drawRect(position, size);

		if (mass != 0) {
			rend->setColor(0, 1, 0);
			rend->drawCircle(centerOfMass, sqrt(mass));
		}

		if (child0 != nullptr)
			child0->render(rend, i + 1);
		if (child1 != nullptr)
			child1->render(rend, i + 1);
		if (child2 != nullptr)
			child2->render(rend, i + 1);
		if (child3 != nullptr)
			child3->render(rend, i + 1);
}



void Node::simulate(Body* body2) {
	if (this->body != body2 && body2->getMass() != 0) {
		vector2d vd = (centerOfMass.subvec(body2->position));
		float d2 = vd.magnitudesq();
		float d = sqrtf(d2);
		vd = vd.normalize(d);

		if (body != nullptr && body->getMass() != 0) {
			if (d <= body2->getRadius() + body->getRadius()) {

				//if (d/EPS < body2->getRadius() + body->getRadius()) {
				//	cout << "\033[1;33m FUSION\033[0m" << endl;
				//	
				//	body2->position = (body2->position.mulf(body2->getMass()) + body->position.mulf(body->getMass())).divf(body2->getMass() + body->getMass());
				//	body2->velocity = (body2->velocity.mulf(body2->getMass()) + body->velocity.mulf(body->getMass())).divf(body2->getMass() + body->getMass());
				//	body2->acceleration.clear();
				//	body2->setMass(body2->getMass() + body->getMass());

				//	body->setMass(0);
				//	body->position = vector2d(0, 0);
				//	body->velocity = vector2d(0, 0);
				//	body->acceleration = vector2d(0, 0);
				//	return;
				//}

				vector2d v = body2->velocity.mulf(body2->getMass()).addvec(body->velocity.mulf(body->getMass())).divf(body2->getMass() + body->getMass());

				float ps = d - (body2->getRadius() + body->getRadius());

				body->velocity = v;
				body2->velocity = v;
				
				body2->velocity += vd.mulf(ps * body->getMass() / (body2->getMass() + body->getMass()));
				return;
			}
			body2->acceleration.setaddvec(vd.mulf(G * mass / d2));
			return;
		}

		if (size.x / (d) < PHI) {
			body2->acceleration.setaddvec(vd.mulf(G * mass / d2));
			return;
		}

		if (child0 != nullptr)
			child0->simulate(body2);
		if (child1 != nullptr)
			child1->simulate(body2);
		if (child2 != nullptr)
			child2->simulate(body2);
		if (child3 != nullptr)
			child3->simulate(body2);
		return;
	}
}
void Node::clear(bool t)
{
	if (child0 != nullptr) {
		child0->clear(true);
	}
	if (child1 != nullptr) {
		child1->clear(true);
	}
	if (child2 != nullptr) {
		child2->clear(true);
	}
	if (child3 != nullptr) {
		child3->clear(true);
	}


	if (t) {
		mass = 0;
		centerOfMass = vector2d();
		body = nullptr;
		hasChildren = false;

		delete child0;
		delete child1;
		delete child2;
		delete child3;
		child0 = nullptr;
		child1 = nullptr;
		child2 = nullptr;
		child3 = nullptr;
	}
}
