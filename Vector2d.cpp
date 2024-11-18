#include "Vector2d.h"


// constructors
Vector2d::Vector2d(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2d::Vector2d() {

}

// operators
Vector2d Vector2d::operator+(Vector2d other) {
	return Vector2d(x + other.x, y + other.y);
}

Vector2d Vector2d::operator-(Vector2d other) {
	return Vector2d(x - other.x, y - other.y);
}

Vector2d Vector2d::operator+=(Vector2d other) {
	return Vector2d(x += other.x, y += other.y);
}

Vector2d Vector2d::operator-=(Vector2d other) {
	return Vector2d(x -= other.x, y -= other.y);
}

void Vector2d::operator=(Vector2d other) {
	this->x = other.x;
	this->y = other.y;
}

Vector2d Vector2d::operator*=(float a) {
	return Vector2d(x *= a, y *= a);
}

Vector2d Vector2d::operator*(float a) {
	return Vector2d(x * a, y * a);
}

bool Vector2d::operator==(Vector2d other) {
	return x == other.x && y == other.y;
}

Vector2d::operator Vector2f() {
	return Vector2f(x, y);
}


// functions
float Vector2d::Dot(Vector2d other) {
	return (x * other.x) + (y * other.y);
}

void Vector2d::normalize() {
	float mag = getMagnitude();
	if (mag == 0) return;
	this->x /= mag;
	this->y /= mag;
}


// byrg3 L length bta3 L vector (MOTAGAH)
float Vector2d::getMagnitude() {
	return sqrt((x * x) + (y * y));
}

Vector2d Vector2d::getNormalized() {
	float mag = getMagnitude();
	return Vector2d(x / mag, y / mag);
}

// L 3amodiiii
Vector2d Vector2d::getNormal() {

	return Vector2d(-y, x);
}