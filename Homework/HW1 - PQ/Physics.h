#pragma once
#include "Ball.h"
#include "Window.h"

class Physics {

public:
	
	/// <summary>The target physics update rate in updates per second.</summary>
	static const int UpdateRate = 100;

	/// <summary>
	/// The target physics update rate in seconds.
	/// This is calculated from UpdateRate.
	/// </summary>
	static double DeltaTime;

	static void UpdateBall(Ball& ball);

};

