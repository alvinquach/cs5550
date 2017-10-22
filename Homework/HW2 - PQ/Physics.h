#pragma once
#include "Window.h"
#include "Scene.h"

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

	static void CheckRobotBaseWorldCollision(Vector3f& position, Vector3f& velocity);

};