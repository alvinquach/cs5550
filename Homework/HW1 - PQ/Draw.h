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

private:

	static ColorRGB CalculateHightlightColor(ColorRGB& color);

	static void SetGlColor3f(ColorRGB& color);

};
