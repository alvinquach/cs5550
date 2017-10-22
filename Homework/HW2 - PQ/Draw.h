// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#pragma once
#define _USE_MATH_DEFINES
#include <windows.h>
#include <cmath>
#include "Window.h"
#include "Vector3f.h"
#include "ColorRGB.h"
//#include "Ball.h"

class Draw {

public:

	static void DrawAxes();

	static void DrawFloor(GLenum renderMode);

	static void DrawRobot(GLenum renderMode);

	//static void DrawBall(Ball& ball);

	//static void DrawSelectedBall(Ball& ball);

private:

	static float CircleVertexCount;
	static float AxesLength;
	static float RoomFloorThickness;

	// TODO Add wall thickness if time permits.

	static ColorRGB RoomFloorColor;
	static float RobotBaseRadius;
	static ColorRGB RobotBaseColor;

	static void DrawRobotBase(GLenum renderMode);

	static void DrawRobotUpperArm(GLenum renderMode);

	static void SetGlColor3f(ColorRGB& color);

	//static void SetGlColor4f(ColorRGB& color, float alpha);

};