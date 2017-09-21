#pragma once
#include "Vector2f.h"
#include "ColorRGB.h"

class Ball {
public:
	static const int VertexCount;
	static const float Density;
	static const float DefaultRadius;
	Ball();
	Ball(float radius);
	~Ball();
	Vector2f& getPosition();
	void setPosition(Vector2f& position);
	Vector2f& getVelocity();
	void setVelocity(Vector2f& velocity);
	float getRadius();
	void setRadius(float radius);
	ColorRGB& getColor();
	void setColor(ColorRGB& color);
	bool getLocked();
	float getMass();
private:
	Vector2f position;
	Vector2f velocity;
	float radius;
	ColorRGB color;
	bool locked;
};