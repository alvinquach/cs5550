// Alvin Quach, 300793745
// CS5550 F17 - HW1 PQ

#pragma once
#define _USE_MATH_DEFINES
#include <windows.h>
#include <cmath>
#include <gl/Gl.h>
#include "Ball.h"
#include "glut.h"
#include "Window.h"

class Draw {

public:

	static void SetWindow(float left, float right, float bottom, float top);

	static void DrawBall(Ball& ball);

	static void DrawSelectedBall(Ball& ball);

private:

	static float BallOutlineThickness;

	static float BallSelectedPulsePeriod;

	static float BallSelectedMaxOpacity;

	static float BallGhostOpacity;

	static void SetGlColor3f(ColorRGB& color);

	static void SetGlColor4f(ColorRGB& color, float alpha);

};

