#pragma once
#define _USE_MATH_DEFINES
#include <windows.h>
#include <iostream>
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

	static float BallSelectedOutlineThickness;

	static void SetGlColor3f(ColorRGB& color);

};

