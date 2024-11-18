#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Vector2d {
public:
	float x;
	float y;

	// constructors
	Vector2d();
	Vector2d(float x, float y);
	
	// operators 
	Vector2d operator+(Vector2d other);
	Vector2d operator-(Vector2d other);
	Vector2d operator+=(Vector2d other);
	Vector2d operator-=(Vector2d other);
	void operator=(Vector2d other);
	Vector2d operator*=(float a);
	Vector2d operator*(float a);
	bool operator==(Vector2d other);

	// functions
	void normalize();
	float Dot(Vector2d other);
	float getMagnitude();
	Vector2d getNormalized();
	operator Vector2f();
	Vector2d getNormal();
};
