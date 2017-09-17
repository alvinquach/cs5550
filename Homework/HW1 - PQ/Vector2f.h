#pragma once
#include "Point2f.h"

class Vector2f : public Point2f {
public:

	Vector2f();

	Vector2f(float x, float y);

	float getMagnitude();

	///	<summary>
	///		Make the vector have the specified magnitude.
	///		The vector's direction will remain unchanged.
	///	</summary>
	///	<param name='magnitude'>The vector's new magnitude.</param>
	void setMagnitude(float magnitude);

	///	<summary>Make the vector have a magnitude of 1.</summary>
	void normalize();

	Vector2f operator +(Vector2f anotherVector);
	Vector2f operator -(Vector2f anotherVector);
	float dot(Vector2f anotherVector);
	Vector2f cross(Vector2f anotherVector);
	
};

Vector2f operator *(float scalar, Vector2f vector);
Vector2f operator /(Vector2f vector, float scalar);