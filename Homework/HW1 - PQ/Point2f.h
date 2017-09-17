#pragma once

class Point2f {
public:
	Point2f();
	Point2f(float x, float y);
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
protected:
	float x;
	float y;
};