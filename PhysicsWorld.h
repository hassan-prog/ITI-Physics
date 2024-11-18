#pragma once
#include "Particle.h"
#include "Collider.h"
#include "AABBCollider.h"
#include "SATCollider.h"
#include <list>

using namespace std;

class PhysicsWorld {
private:
	list<Particle*> particles;
	list<Particle*> particles2;
public:
	void addParticle(Particle* particle);
	void Update(float deltaTime, bool& collided, bool& squareCollided);
	void checkTwoCircleCollision(bool& collided);
	void checkTwoSquareCollision(bool& squareCollided);
	void elasticEffect(Particle* p1, Particle* p2);
	static const Vector2d gravity;
};
