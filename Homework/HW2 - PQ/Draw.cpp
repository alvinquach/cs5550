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

	// Draw the base.
	DrawRobotBase(robot, renderMode);

	// Angle the upper arm assembly.
	glPushMatrix();
	glRotatef(robot.getCurrentState().upperArmAngle * 180 / M_PI, 0, 0, 1);

	// Draw the upper arm.
	DrawRobotUpperArm(robot, renderMode);

	// Position the elbow.
	glPushMatrix();
	glTranslatef(0, Robot::RobotUpperArmLength, 0);
	
	// Draw the elbow.
	DrawRobotElbow(robot, renderMode);

	// Angle the lower arm assembly.
	glPushMatrix();
	glRotatef(robot.getCurrentState().lowerArmAngle * 180 / M_PI, 0, 0, 1);

	// Draw the lower arm.
	DrawRobotLowerArm(robot, renderMode);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void Draw::DrawRobotBase(Robot& robot, GLenum renderMode) {
	SetGlColor3f(Robot::RobotBaseColor);
	glPushMatrix();
	glTranslatef(0, 0.02, 0);
	glRotatef(90, 1, 0, 0);
	GLUquadricObj * baseAssm = gluNewQuadric();
	gluQuadricDrawStyle(baseAssm, renderMode);
	gluCylinder(baseAssm, Robot::RobotBaseRadius, Robot::RobotBaseRadius, 0.02, CircleVertexCount, 1);
	gluDisk(baseAssm, 0, Robot::RobotBaseRadius, CircleVertexCount, 1);
	SetGlColor3f(Robot::RobotJointColor);
	gluSphere(baseAssm, Robot::RobotShoulderJointRadius, CircleVertexCount, 24);
	glPopMatrix();
}

void Draw::DrawRobotUpperArm(Robot& robot, GLenum renderMode) {
	SetGlColor3f(Robot::RobotUpperArmColor);
	glPushMatrix();
	glRotatef(90, -1, 0, 0);
	GLUquadricObj * upperArm = gluNewQuadric();
	gluQuadricDrawStyle(upperArm, renderMode);
	gluCylinder(upperArm, Robot::RobotUpperArmRadius, Robot::RobotUpperArmRadius, Robot::RobotUpperArmLength, CircleVertexCount, 1);
	glPopMatrix();
}

void Draw::DrawRobotElbow(Robot& robot, GLenum renderMode) {
	SetGlColor3f(Robot::RobotJointColor);
	GLUquadricObj * elbow = gluNewQuadric();
	gluQuadricDrawStyle(elbow, renderMode);
	gluSphere(elbow, Robot::RobotElbowJointRadius, CircleVertexCount, 24);
}

void Draw::DrawRobotLowerArm(Robot& robot, GLenum renderMode) {
	SetGlColor3f(Robot::RobotLowerArmColor);
	glPushMatrix();
	glRotatef(90, -1, 0, 0);
	GLUquadricObj * lowerArm = gluNewQuadric();
	gluQuadricDrawStyle(lowerArm, renderMode);
	gluCylinder(lowerArm, Robot::RobotLowerArmRadius, Robot::RobotLowerArmRadius, Robot::RobotLowerArmLength, CircleVertexCount, 1);
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


