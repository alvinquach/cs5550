// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#pragma once
#define _USE_MATH_DEFINES
#include <windows.h>
#include <cmath>
#include "Window.h"
#include "Vector3f.h"
//#include "Ball.h"

class Draw {

public:

	/// <summary>Thickness of the floor.</summary>
	static const float RoomFloorThickness;

	// TODO Add wall thickness if time permits.

	static void DrawAxes();

	static void DrawFloor();

	//static void DrawBall(Ball& ball);

	//static void DrawSelectedBall(Ball& ball);

private:

	/// <summary>Length of the rendered world axes.</summary>
	static const float AxesLength;

	//static float BallOutlineThickness;

	//static float BallSelectedPulsePeriod;

	//static float BallSelectedMaxOpacity;

	//static float BallGhostOpacity;

	//static void SetGlColor3f(ColorRGB& color);

	//static void SetGlColor4f(ColorRGB& color, float alpha);

};