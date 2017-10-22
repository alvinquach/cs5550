#define _USE_MATH_DEFINES
#include <cmath>
#include "Draw.h"
#include "Scene.h"

/// <summary>How many vertices to use for circular faces.</summary>
float Draw::CircleVertexCount = 48;

/// <summary>Length of the rendered world axes.</summary>
float Draw::AxesLength = 100.0;

/// <summary>Thickness of the floor.</summary>
float Draw::RoomFloorThickness = 0.1;

/// <summary>Color of the floor.</summary>
ColorRGB Draw::RoomFloorColor = ColorRGB(127, 127, 127);

/// <summary>Radius of the robot's base.</summary>
float Draw::RobotBaseRadius = 0.5;

/// <summary>Color of the robot's base.</summary>
ColorRGB Draw::RobotBaseColor = ColorRGB(197, 17, 98);

void Draw::DrawAxes() {

	glBegin(GL_LINES);

	//x
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(AxesLength, 0, 0);
	//y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, AxesLength, 0);
	//z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, AxesLength);

	glEnd();

}

void Draw::DrawFloor(GLenum renderMode) {
	SetGlColor3f(RoomFloorColor);
	glPushMatrix();
	glTranslatef(0, -Draw::RoomFloorThickness / 2, 0);
	glScalef(Scene::GetRoomDimensions().getX(), Draw::RoomFloorThickness, Scene::GetRoomDimensions().getZ());
	if (renderMode == GLU_FILL)
		glutSolidCube(1);
	else
		glutWireCube(1);
	glPopMatrix();
}

void Draw::DrawRobot(GLenum renderMode) {

	Robot& robot = Scene::GetRobot();

	// Position the robot.
	glPushMatrix();
	Translate3f(robot.getCurrentState().position);
	glRotatef(robot.getCurrentState().baseAngle * 180 / M_PI, 0, -1, 0);

	// Draw the arm components
	DrawRobotBase(robot, renderMode);
	//DrawRobotUpperArm(renderMode);

	glPopMatrix();
}

void Draw::DrawRobotBase(Robot& robot, GLenum renderMode) {
	SetGlColor3f(RobotBaseColor);
	glPushMatrix();
	glTranslatef(0, 0.02, 0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj * qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, renderMode);
	gluCylinder(qobj, RobotBaseRadius, RobotBaseRadius, 0.02, CircleVertexCount, 1);
	gluDisk(qobj, 0, RobotBaseRadius, CircleVertexCount, 1);
	gluSphere(qobj, RobotBaseRadius / 2.5, CircleVertexCount, 24);
	glPopMatrix();
}

void Draw::DrawRobotUpperArm(Robot& robot, GLenum renderMode) {
	SetGlColor3f(RobotBaseColor);
	glPushMatrix();
	glTranslatef(0, 0.02, 0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj * qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, renderMode);
	gluCylinder(qobj, RobotBaseRadius, RobotBaseRadius, 0.02, CircleVertexCount, 1);
	gluDisk(qobj, 0, RobotBaseRadius, CircleVertexCount, 1);
	gluSphere(qobj, RobotBaseRadius / 2.5, CircleVertexCount, 24);
	glPopMatrix();
}

void Draw::SetGlColor3f(ColorRGB& color) {
	glColor3f(color.getFloatR(), color.getFloatG(), color.getFloatB());
}

void Draw::Translate3f(Vector3f& position) {
	glTranslatef(
		position.getX(),
		position.getY(),
		position.getZ()
	);
}

void Draw::Scale3f(Vector3f& scale) {
	glScalef(
		scale.getX(),
		scale.getY(),
		scale.getZ()
	);
}


