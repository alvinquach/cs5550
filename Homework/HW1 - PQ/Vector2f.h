#pragma once
#include "Vector.h"

/// <summary>Represents a two dimensional vector with values stored in float.</summary>
class Vector2f : public Vector<float, 2> {
public:

	Vector2f();

	Vector2f(float x, float y);

	/// <summary>Shorthand for writing Vector2f(0, 1).</summary>
	static Vector2f up();

	///	<summary>Shorthand for writing Vector2f(1, 0).</summary>
	static Vector2f right();

	///	<summary>Shorthand for writing Vector2f(0, -1).</summary>
	static Vector2f down();

	///	<summary>Shorthand for writing Vector2f(-1, 0).</summary>
	static Vector2f left();

	///	<summary>Shorthand for writing Vector2f(0, 0).</summary>
	static Vector2f zero();

	float getX();
	void setX(float x);
	float getY();
	void setY(float y);



	/// <summary>Scale the vector's magnitude by the specified amount.</summary>
	///	<param name='scale'>The scaling factor.</param>
	void scale();

};

// Free function operator overloads.
Vector2f operator *(float scalar, Vector2f vector);