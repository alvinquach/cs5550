#pragma once
#include "Window.h"
#include "Scene.h"
#include "Ball.h"

class Physics {

public:

	/// <summary>The target number of times to recalculate the physics for each rendered frame.</summary>
	static const int UpdatesPerFrame;

	/// <summary>
	/// The target physics update rate in seconds.
	/// This is calculated from UpdateRate.
	/// </summary>
	static const double DeltaTime;

	static void Update();

private:

	static const float RobotWorldCollisionSlowDownFactor;
	static const float BallWorldCollisionSlowDownFactor;

	static void UpdateBalls();
	static void UpdateBallPosition(Ball& ball);
	static void ApplyGravityToBall(Ball& ball);

	static bool CheckWorldCollision(bool checkVertical, float radius, Vector3f& position, Vector3f& velocity, float slowDownFactor);

};