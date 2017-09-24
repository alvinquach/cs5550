#pragma once
#include "Vector2f.h"
#include "ColorRGB.h"

struct AvailableColor {
	ColorRGB color;
	ColorRGB highlight;
	int counter;
};

class Ball {
public:

	static const int VertexCount;

	static const float Density;

	static const float DefaultRadius;

	static const float MinRadius;

	static const float MaxRadius;

	static const float MaxMomentum;

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

	/// <summary>
	/// Sets a new radius for the ball.
	/// Momentum of the ball will not be preserved.
	/// </summary>
	void setRadius(float radius);

	/// <summary>
	/// Sets a new radius for the ball.
	/// This function can optionally preserve the ball's momentum by adjusting the ball's speed.
	/// </summary>
	/// <param name='preserveMomentum'>
	/// Whether to preserve the ball's momentum.
	/// </param>
	void setRadius(float radius, bool preserveMomentum);

	ColorRGB& getColor();
	void setColor(ColorRGB& color);
	ColorRGB& getHighlight();
	void setHighlight(ColorRGB& highlight);
	bool isFilled();
	void toggleFilled();
	bool isSolid();
	void setSolid(bool solid);
	bool isLocked();
	void setLocked(bool locked);

	float getSpeed();

	/// <summary>
	/// Sets the new speed of the ball.
	/// The speed will be limited based on the ball's current mass and maximum allowed momentum.
	/// </summary>
	/// <param name='speed'>
	/// The ball's new speed.
	/// </param>
	void setSpeed(float speed);

	float getMass();
private:
	static int RandomBallCounter;
	static vector<AvailableColor> AvailableColors;
	static AvailableColor& GetRandomColor();
	Vector2f position;
	Vector2f velocity;
	float radius;
	ColorRGB color;
	ColorRGB highlight;
	bool filled;
	bool solid;
	bool locked;
};