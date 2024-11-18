#include "Particle.h"
#include <iostream>

Particle::Particle(Vector2d position, float mass, float drag, string type) : type(type) {
	this->position = position;
	this->forces = Vector2d(0, 0);
	this->velocity = Vector2d(0, 0);
	this->mass = mass;
	this->drag = drag;

	collider.center = position;
	collider.r = 15;
	if (type == "circle") {
		aabbCollider.updatePosition(position);
		aabbCollider.lowerRight = Vector2d(position.x + 2 * 15.f, position.y + 2 * 15.f);
	}
	else if (type == "square") {
		satCollider.updatePosition(position);
		satCollider.points.push_back(position);
		satCollider.points.push_back(Vector2d(position.x + 40, position.y));
		satCollider.points.push_back(Vector2d(position.x, position.y + 40));
		satCollider.points.push_back(Vector2d(position.x + 40, position.y + 40));
	}
}

void Particle::Update(float dt) {

	/*if (velocity.getMagnitude() > 1) {
		Vector2d dragForce = velocity * -0.5 * drag * velocity.getMagnitude();
		this->addForce(dragForce);
	}*/
	acceleration = forces * (1 / mass);
	velocity += acceleration * dt; // integration
	position += velocity * dt; // integration
	forces = Vector2d(0, 0);


	// Comment 1 collider to make the other work (collider and aabbCollider) 
	//collider.center = position;
	aabbCollider.updatePosition(position);

	// satCollider works on two different objects other than the circle
	satCollider.updatePosition(position);

}

void Particle::addForce(Vector2d force) {
	forces += force;
}

void Particle::addDrag(float drag) {
	this->drag += drag;
}
