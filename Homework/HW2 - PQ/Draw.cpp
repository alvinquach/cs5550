// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

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

	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(AxesLength, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, AxesLength, 0);

	glColor3f(0, 0, 1);
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
	glRotatef(robot.getCurrentState().upperArmAngle * 180 / M_PI, 0, 0, -1);

	// Draw the upper arm.
	DrawRobotUpperArm(robot, renderMode);

	// Position the elbow.
	glPushMatrix();
	glTranslatef(0, Robot::RobotUpperArmLength, 0);
	
	// Draw the elbow.
	DrawRobotElbow(robot, renderMode);

	// Angle the lower arm assembly.
	glPushMatrix();
	glRotatef(robot.getCurrentState().lowerArmAngle * 180 / M_PI, 0, 0, -1);

	// Draw the lower arm.
	DrawRobotLowerArm(robot, renderMode);

	// Position the wrist.
	glPushMatrix();
	glTranslatef(0, Robot::RobotLowerArmLength, 0);

	// Draw the wrist.
	DrawRobotWrist(robot, renderMode);

	// Draw the ball in the hand.
	DrawRobotBallInHand(robot, renderMode);

	// Angle the hand assembly.
	glPushMatrix();
	glRotatef(robot.getCurrentState().handAngle * 180 / M_PI, 0, 0, -1);

	// Draw the hand.
	DrawRobotHand(robot, renderMode);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
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

void Draw::DrawRobotWrist(Robot& robot, GLenum renderMode) {
	SetGlColor3f(Robot::RobotJointColor);
	GLUquadricObj * wrist = gluNewQuadric();
	gluQuadricDrawStyle(wrist, renderMode);
	gluSphere(wrist, Robot::RobotWristJointRadius, CircleVertexCount, 24);
}

void Draw::DrawRobotBallInHand(Robot& robot, GLenum renderMode) {
	if (!robot.isHoldingBall()) {
		return;
	}
	glPushMatrix();
	glTranslatef(0.069, Robot::HandLength, 0);
	SetGlColor3f(Ball::Color);
	if (renderMode == GLU_FILL)
		glutSolidSphere(Ball::Radius, CircleVertexCount, 24);
	else
		glutWireSphere(Ball::Radius, CircleVertexCount, 24);
	glPopMatrix();
}

void Draw::DrawRobotHand(Robot& robot, GLenum renderMode) {
	DrawRobotThumb(robot, renderMode);
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(0, 0.025, (i - 1.25) * 0.025);
		glRotatef((i - 1) * 4.5, 1, 0, 0);
		glScalef(Robot::FingerScale[i], Robot::FingerScale[i], Robot::FingerScale[i]);
		DrawRobotFinger(robot, renderMode, 1.0);
		glPopMatrix();
	}
}

void Draw::DrawRobotThumb(Robot& robot, GLenum renderMode) {

	float handScale = 1.9;

	// Positioning
	glPushMatrix();
	glTranslatef(0, 0.015, -0.05);
	glRotatef(-16.0, 1, 0, 0);
	glRotatef(3.1 + robot.getCurrentState().thumbAngle * 180 / M_PI, 0, 0, -1);

	// Palm part
	SetGlColor3f(Robot::HandColor);
	glPushMatrix();
	glTranslatef(0, Robot::HandLength / handScale / 2, 0);
	glScalef(Robot::HandThickness, Robot::HandLength / handScale, Robot::HandThickness);
	if (renderMode == GLU_FILL)
		glutSolidCube(1);
	else
		glutWireCube(1);
	glPopMatrix();

	// First knuckle
	glPushMatrix();
	glTranslatef(0, Robot::HandLength / handScale, 0);
	SetGlColor3f(Robot::RobotJointColor);
	if (renderMode == GLU_FILL)
		glutSolidSphere(Robot::ThumbProximalDigitThickness, CircleVertexCount / 2, 12);
	else
		glutWireSphere(Robot::ThumbProximalDigitThickness, CircleVertexCount / 2, 12);

	// Angle the thumb section
	glPushMatrix();
	glRotatef(robot.getCurrentState().thumbAngle * 180 / M_PI, 1, 0, 0);

	// Proximal digit
	SetGlColor3f(Robot::ThumbProximalDigitColor);
	glPushMatrix();
	glTranslatef(0, Robot::ThumbProximalDigitLength / 2, 0);
	glScalef(Robot::ThumbProximalDigitThickness, Robot::ThumbProximalDigitLength, Robot::ThumbProximalDigitThickness);
	if (renderMode == GLU_FILL)
		glutSolidCube(1);
	else
		glutWireCube(1);
	glPopMatrix();

	// Second knuckle
	glPushMatrix();
	glTranslatef(0, Robot::ThumbProximalDigitLength, 0);
	SetGlColor3f(Robot::RobotJointColor);
	if (renderMode == GLU_FILL)
		glutSolidSphere(Robot::ThumbDistalDigitThickness, CircleVertexCount / 2, 12);
	else
		glutWireSphere(Robot::ThumbDistalDigitThickness, CircleVertexCount / 2, 12);

	// Angle the thumb section
	glPushMatrix();
	glRotatef(robot.getCurrentState().thumbAngle * 180 / M_PI, 1, 0, 0);

	// Distal digit
	SetGlColor3f(Robot::ThumbDistalDigitColor);
	glPushMatrix();
	glTranslatef(0, Robot::ThumbDistalDigitLength / 2, 0);
	glScalef(Robot::ThumbDistalDigitThickness, Robot::ThumbDistalDigitLength, Robot::ThumbDistalDigitThickness);
	if (renderMode == GLU_FILL)
		glutSolidCube(1);
	else
		glutWireCube(1);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void Draw::DrawRobotFinger(Robot& robot, GLenum renderMode, float scale) {

	// Palm part
	SetGlColor3f(Robot::HandColor);
	glPushMatrix();
	glTranslatef(0, Robot::HandLength / 2, 0);
	glScalef(Robot::HandThickness, Robot::HandLength, Robot::HandThickness);
	if (renderMode == GLU_FILL)
		glutSolidCube(1);
	else
		glutWireCube(1);
	glPopMatrix();

	// First knuckle
	glPushMatrix();
	glTranslatef(0, Robot::HandLength, 0);
	SetGlColor3f(Robot::RobotJointColor);
	if (renderMode == GLU_FILL)
		glutSolidSphere(Robot::FingerProximalDigitThickness, CircleVertexCount / 2, 12);
	else
		glutWireSphere(Robot::FingerProximalDigitThickness, CircleVertexCount / 2, 12);

	// Angle the finger section
	glPushMatrix();
	glRotatef(robot.getCurrentState().fingerAngle * 180 / M_PI, 0, 0, -1);

	// Proximal digit
	SetGlColor3f(Robot::FingerProximalDigitColor);
	glPushMatrix();
	glTranslatef(0, Robot::FingerProximalDigitLength / 2, 0);
	glScalef(Robot::FingerProximalDigitThickness, Robot::FingerProximalDigitLength, Robot::FingerProximalDigitThickness);
	if (renderMode == GLU_FILL)
		glutSolidCube(1);
	else
		glutWireCube(1);
	glPopMatrix();

	// Second knuckle
	glPushMatrix();
	glTranslatef(0, Robot::FingerProximalDigitLength, 0);
	SetGlColor3f(Robot::RobotJointColor);
	if (renderMode == GLU_FILL)
		glutSolidSphere(Robot::FingerMiddleDigitThickness, CircleVertexCount / 2, 12);
	else
		glutWireSphere(Robot::FingerMiddleDigitThickness, CircleVertexCount / 2, 12);

	// Angle the finger section
	glPushMatrix();
	glRotatef(robot.getCurrentState().fingerAngle * 180 / M_PI, 0, 0, -1);

	// Middle digit
	SetGlColor3f(Robot::FingerMiddleDigitColor);
	glPushMatrix();
	glTranslatef(0, Robot::FingerMiddleDigitLength / 2, 0);
	glScalef(Robot::FingerMiddleDigitThickness, Robot::FingerMiddleDigitLength, Robot::FingerMiddleDigitThickness);
	if (renderMode == GLU_FILL)
		glutSolidCube(1);
	else
		glutWireCube(1);
	glPopMatrix();

	// Last knuckle
	glPushMatrix();
	glTranslatef(0, Robot::FingerMiddleDigitLength, 0);
	SetGlColor3f(Robot::RobotJointColor);
	if (renderMode == GLU_FILL)
		glutSolidSphere(Robot::FingerDistalDigitThickness, CircleVertexCount / 2, 12);
	else
		glutWireSphere(Robot::FingerDistalDigitThickness, CircleVertexCount / 2, 12);

	// Angle the finger section
	glPushMatrix();
	glRotatef(robot.getCurrentState().fingerAngle * 180 / M_PI, 0, 0, -1);

	// Distal digit
	SetGlColor3f(Robot::FingerDistalDigitColor);
	glPushMatrix();
	glTranslatef(0, Robot::FingerDistalDigitLength / 2, 0);
	glScalef(Robot::FingerDistalDigitThickness, Robot::FingerDistalDigitLength, Robot::FingerDistalDigitThickness);
	if (renderMode == GLU_FILL)
		glutSolidCube(1);
	else
		glutWireCube(1);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void Draw::DrawBall(Ball& ball, GLenum renderMode) {
	glPushMatrix();
	Translate3f(ball.getPosition());
	SetGlColor3f(Ball::Color);
	if (renderMode == GLU_FILL)
		glutSolidSphere(Ball::Radius, CircleVertexCount, 24);
	else
		glutWireSphere(Ball::Radius, CircleVertexCount, 24);
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


