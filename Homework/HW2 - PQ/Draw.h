// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#pragma once
#include <windows.h>
#include "Vector3f.h"
#include "ColorRGB.h"
#include "glut.h"
#include "Robot.h"
#include "Ball.h"

class Draw {

public:

	static void DrawAxes();

	static void DrawFloor(GLenum renderMode);

	static void DrawRobot(GLenum renderMode);

	static void DrawBall(Ball& ball, GLenum renderMode);


	//static void DrawBall(Ball& ball);

	//static void DrawSelectedBall(Ball& ball);

private:

	static float CircleVertexCount;
	static float AxesLength;
	static float RoomFloorThickness;

	// TODO Add wall thickness if time permits.

	static ColorRGB RoomFloorColor;

	static void DrawRobotBase(Robot& robot, GLenum renderMode);

	static void DrawRobotUpperArm(Robot& robot, GLenum renderMode);

	static void DrawRobotElbow(Robot& robot, GLenum renderMode);

	static void DrawRobotLowerArm(Robot& robot, GLenum renderMode);

	static void DrawRobotWrist(Robot& robot, GLenum renderMode);

	static void DrawRobotBallInHand(Robot& robot, GLenum renderMode);

	static void DrawRobotHand(Robot& robot, GLenum renderMode);

	static void DrawRobotThumb(Robot& robot, GLenum renderMode);

	static void DrawRobotFinger(Robot& robot, GLenum renderMode, float scale);

	static void SetGlColor3f(ColorRGB& color);

	static void Translate3f(Vector3f& position);

	static void Scale3f(Vector3f& scale);

	//static void SetGlColor4f(ColorRGB& color, float alpha);

};