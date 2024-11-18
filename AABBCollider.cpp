#include "AABBCollider.h"

void AABBCollider::updatePosition(Vector2d position) {
	Vector2d delta = position - this->position;
	upperLeft += delta;
	lowerRight += delta;
	this->position = position;
}

bool AABBCollider::checkCollision(AABBCollider other) {
	if (upperLeft.x >= other.upperLeft.x && upperLeft.y >= other.upperLeft.y
		&& upperLeft.x <= other.lowerRight.x && upperLeft.y <= other.lowerRight.y)
		return true;

	if (lowerRight.x <= other.lowerRight.x && lowerRight.y <= other.lowerRight.y
		&& lowerRight.x >= other.upperLeft.x && lowerRight.y >= other.upperLeft.y)
		return true;

	return false;
}
