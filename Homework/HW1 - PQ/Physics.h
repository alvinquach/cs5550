#pragma once
#include "Ball.h"
#include "Window.h"

class Physics {

public:
	
	/// <summary>The target physics update rate in updates per second.</summary>
	static const int UpdateRate;

	/// <summary>
	/// The target physics update rate in seconds.
	/// This is calculated from UpdateRate.
	/// </summary>
	static const double DeltaTime;

	static void UpdateBall(Ball& ball);

};

