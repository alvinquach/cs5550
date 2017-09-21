#pragma once
#include "Vector.h"

/// <summary>Represents a two dimensional vector with values stored in float.</summary>
class Vector2f : public Vector<float, 2> {
public:

	Vector2f();

	Vector2f(float x, float y);

	/// <summary>Shorthand for writing Vector2f(0, 1).</summary>
	static Vector2f Up();

	/// <summary>Shorthand for writing Vector2f(1, 0).</summary>
	static Vector2f Right();

	/// <summary>Shorthand for writing Vector2f(0, -1).</summary>
	static Vector2f Down();

	/// <summary>Shorthand for writing Vector2f(-1, 0).</summary>
	static Vector2f Left();

	/// <summary>Shorthand for writing Vector2f(0, 0).</summary>
	static Vector2f Zero();

	float getX();
	void setX(float x);
	float getY();
	void setY(float y);

	/// <summary>Returns a unit vector with the same direction as this vector.</summary>
	Vector2f unitVector();

	// Operator overloads.
	Vector2f operator +(Vector2f anotherVector);
	Vector2f operator -(Vector2f anotherVector);
	Vector2f operator /(float scalar);

};

// Free function operator overloads.
Vector2f operator *(float scalar, Vector2f vector);