#include "PhysicsWorld.h"

void PhysicsWorld::addParticle(Particle* particle) {
	particles.push_back(particle);
}
void PhysicsWorld::Update(float deltaTime, bool& collided, bool& squareCollided) {
	list<Particle*>::iterator iter;

	for (iter = particles.begin(); iter != particles.end(); ++iter) {
		(*iter)->Update(deltaTime);
	}
	checkTwoCircleCollision(collided);
	checkTwoSquareCollision(squareCollided);
}

void PhysicsWorld::checkTwoCircleCollision(bool& collided) {
	list<Particle*>::iterator itr1, itr2;

	for (itr1 = particles.begin(); itr1 != particles.end(); ++itr1) {
		Particle* p1 = *itr1;
		//Collider c1 = p1->collider;
		if (p1->type != "circle") continue;
		AABBCollider c1 = p1->aabbCollider;

		for (itr2 = std::next(itr1); itr2 != particles.end(); ++itr2) {
			Particle* p2 = *itr2;
			//Collider c2 = p2->collider;
			AABBCollider c2 = p2->aabbCollider;

			if (c1.checkCollision(c2)) {
				std::cout << "circle Collision\n";
				collided = true;
				elasticEffect(p1, p2);
			}
		}
	}
}

void PhysicsWorld::checkTwoSquareCollision(bool& squareCollided) {
	list<Particle*>::iterator itr1, itr2;

	for (itr1 = particles.begin(); itr1 != particles.end(); ++itr1) {
		Particle* p1 = *itr1;
		if (p1->type != "square") continue;
		SATCollider c1 = p1->satCollider;

		for (itr2 = std::next(itr1); itr2 != particles.end(); ++itr2) {
			Particle* p2 = *itr2;
			SATCollider c2 = p2->satCollider;

			if (c1.checkCollision(c2)) {
				std::cout << "square Collision\n";
				squareCollided = true;
				elasticEffect(p1, p2);
			}
		}
	}
}

void PhysicsWorld::elasticEffect(Particle* p1, Particle* p2) {
	Vector2d v1 = p1->velocity;
	float m1 = p1->mass;
	Vector2d x1 = p1->position;

	Vector2d v2 = p2->velocity;
	float m2 = p2->mass;
	Vector2d x2 = p2->position;

	Vector2d normal = x1 - x2;
	float normalmag = normal.getMagnitude();
	Vector2d unitNormal = normal * (1 / normalmag);

	Vector2d relativeVelocity = v1 - v2;
	float dotProduct = relativeVelocity.Dot(unitNormal);

	float coefficient = (2 * m2) / (m1 + m2);
	v1 = v1 - unitNormal * (dotProduct * coefficient);

	normal = x2 - x1;
	normalmag = normal.getMagnitude();
	unitNormal = normal * (1 / normalmag);


	relativeVelocity = v2 - v1; // Recalculate relative velocity for v2
	dotProduct = relativeVelocity.Dot(unitNormal);

	coefficient = (2 * m1) / (m1 + m2);
	v2 = v2 - (unitNormal) * (dotProduct * coefficient);

	p1->velocity = v1;
	p2->velocity = Vector2d(-v2.x, -v2.y);
}