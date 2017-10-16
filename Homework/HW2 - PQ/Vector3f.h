// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#pragma once
#include "Vector.h"

/// <summary>Represents a two dimensional vector with values stored in float.</summary>
class Vector3f : public Vector<float, 3> {
public:

	Vector3f();

	Vector3f(float x, float y);

	/// <summary>Shorthand for writing Vector3f(0, 1).</summary>
	static Vector3f Up();

	/// <summary>Shorthand for writing Vector3f(1, 0).</summary>
	static Vector3f Right();

	/// <summary>Shorthand for writing Vector3f(0, -1).</summary>
	static Vector3f Down();

	/// <summary>Shorthand for writing Vector3f(-1, 0).</summary>
	static Vector3f Left();

	/// <summary>Shorthand for writing Vector3f(0, 0).</summary>
	static Vector3f Zero();

	float getX();
	void setX(float x);
	float getY();
	void setY(float y);

	/// <summary>Returns a unit vector with the same direction as this vector.</summary>
	Vector3f unitVector();

	// Operator overloads.
	Vector3f operator +(Vector3f anotherVector);
	Vector3f operator -(Vector3f anotherVector);
	Vector3f operator /(float scalar);

};

// Free function operator overloads.
Vector3f operator *(float scalar, Vector3f vector);