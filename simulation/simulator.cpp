#include "simulator.h"

void Simulator::update(Env* env)
{
	env->bodies.erase(remove_if(
		env->bodies.begin(), env->bodies.end(),
		[](const Body& x) {
			return x.getMass() == 0; // put your condition here
		}), env->bodies.end());



	for (int i = 0; i < env->bodies.size(); i++) {
		Body* b1 = &env->bodies[i];
		for (int j = i + 1; j < env->bodies.size(); j++) {
			Body* b2 = &env->bodies[j];
			if (b1->getMass() != 0 && b2->getMass() != 0) {
				vector2d u = (b2->position - b1->position);
				float f = b2->getRadius() + b1->getRadius();
				float magsq = u.magnitudesq();

				if (magsq >= f * f) {
					vector2d tmp = u.normalize().mulf(G / magsq);

					b1->acceleration.addvec(tmp.mulf(b2->getMass()));
					b2->acceleration.addvec(tmp.mulf(-b1->getMass()));
				}
				else {
					float nmass = b1->getMass() + b2->getMass();
					b2->position = (b1->position.mulf(b1->getMass()) + b2->position.mulf(b2->getMass())).divf(nmass);
					b2->velocity = (b1->velocity.mulf(b1->getMass()) + b2->velocity.mulf(b2->getMass())).divf(nmass);
					b2->acceleration = (b1->acceleration.mulf(b1->getMass()) + b2->acceleration.mulf(b2->getMass())).divf(nmass);
					b2->setMass(nmass);

					b1->setMass(0);
					b1->position.clear();
					b1->velocity.clear();
					b1->acceleration.clear();
				}
			}
		}
	}

	for (int i = 0; i < env->bodies.size(); i++) {
		Body* b = &env->bodies[i];
		if (b->getMass() != 0) {
			b->velocity += b->acceleration;
			b->position += b->velocity;
			b->acceleration.clear();
		}
	}
}