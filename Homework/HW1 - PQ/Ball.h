#pragma once
#include "Vector2f.h"
#include "ColorRGB.h"

struct AvailableColor {
	ColorRGB color;
	int counter;
};

class Ball {
public:
	static const int VertexCount;
	static const float Density;
	static const float DefaultRadius;
	static const float MinRadius;
	static const float MaxRadius;
	static const float MinInitialRadius;
	static const float MaxInitialRadius;
	static const float MinInitialMomentum;
	static const float MaxInitialMomentum;
	static Ball Random();
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
	static int RandomBallCounter;
	static vector<AvailableColor> AvailableColors;
	static ColorRGB GetRandomColor();
	Vector2f position;
	Vector2f velocity;
	float radius;
	ColorRGB color;
	bool locked;
};