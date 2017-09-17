#pragma once
#include "Vector2f.h"

class Ball {
public:
	Ball();
	~Ball();
	Point2f getPosition();
	void setPosition(Point2f position);
	Vector2f getVelocity();
	void setVelocity(Vector2f velocity);
private:
	Point2f position;
	Vector2f velocity;
};