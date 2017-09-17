#pragma once
#include "Vector2f.h"
#include "ColorRGB.h"

class Ball {
public:
	Ball();
	~Ball();
	Point2f getPosition();
	void setPosition(Point2f position);
	Vector2f getVelocity();
	void setVelocity(Vector2f velocity);
	ColorRGB getColor();
	void setColor(ColorRGB color);
private:
	Point2f position;
	Vector2f velocity;
	ColorRGB color;
};