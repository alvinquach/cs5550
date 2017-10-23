#pragma once
#include "Vector3f.h"
#include "ColorRGB.h"

class Ball {

public:

	/// <summary>The mass of a ball.</summary>
	static const float Mass;

	/// <summary>The radius of a ball.</summary>
	static const float Radius;

	/// <summary>The color of a ball.</summary>
	static ColorRGB Color;

	Ball();

	~Ball();

	Vector3f& getPosition();

	void setPosition(Vector3f& position);

	Vector3f& getVelocity();

	void setVelocity(Vector3f& velocity);

private:
	Vector3f position;
	Vector3f velocity;
};