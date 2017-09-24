#pragma once
#include "Ball.h"
#include "Window.h"

class Physics {

public:
	
	/// <summary>The target number of times to recalculate the physics for each rendered frame.</summary>
	static const int UpdatesPerFrame;

	/// <summary>
	/// The target physics update rate in seconds.
	/// This is calculated from UpdateRate.
	/// </summary>
	static const double DeltaTime;
	
	static void UpdateBalls(vector<Ball>& balls);

private:

	/// <summary>Updates the ball's position based on velocity.</summary>
	static void UpdateBallPosition(Ball& ball);

	/// <summary>Check if the ball has collided with the world, and update its velocity accordingly.</summary>
	static void CheckBallWorldCollision(Ball& ball);

	/// <summary>Check if balls a and b have collided with each other.</summary>
	static bool BallsCollided(Ball& a, Ball& b);

	/// <summary>
	/// Handles the collision between two balls.
	/// This function assumes that both balls have indeed collided with each other.
	/// </summary>
	static void HandleBallCollision(Ball& a, Ball& b);

};

