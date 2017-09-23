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
	
	static void UpdateBall(Ball& ball);

};

