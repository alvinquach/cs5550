#pragma once
#include "Vector2f.h"
#include "ColorRGB.h"

class Ball {
public:
	Ball();
	~Ball();
	Vector2f getPosition();
	void setPosition(Vector2f position);
	Vector2f getVelocity();
	void setVelocity(Vector2f velocity);
	ColorRGB getColor();
	void setColor(ColorRGB color);
private:
	Vector2f position;
	Vector2f velocity;
	ColorRGB color;
};