// Alvin Quach, 300793745
// CS5550 F17 - HW1 PQ

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

	/// <summary>The number of verticies to use when drawing a ball.</summary>
	static const int VertexCount;

	/// <summary>The density of all balls. Used for calculating mass.</summary>
	static const float Density;

	/// <summary>The default radius of a constructed ball.</summary>
	static const float DefaultRadius;

	/// <summary>The smallest amount that a ball's radius can be decreased to.</summary>
	static const float MinRadius;

	/// <summary>The largest amount that a ball's radius can be increased to.</summary>
	static const float MaxRadius;

	/// <summary>
	/// The maximum momentum allowed when increaseing the ball's speed using the up arrow.
	/// This will limit how much a ball's speed can be increased to based on its mass.
	/// This does not limit the max speed/momentum of a ball due to collision or mouse movement.
	/// </summary>
	static const float MaxMomentum;

	/// <summary>Minimum initial radius of a randomly generated ball.</summary>
	static const float MinInitialRadius;

	/// <summary>Maximum initial radius of a randomly generated ball.</summary>
	static const float MaxInitialRadius;

	/// <summary>Minimum initial momentum of a randomly generated ball.</summary>
	static const float MinInitialMomentum;

	/// <summary>Maximum initial momentum of a randomly generated ball.</summary>
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
};