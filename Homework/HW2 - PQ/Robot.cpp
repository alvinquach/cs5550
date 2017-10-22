#define _USE_MATH_DEFINES
#include "Robot.h"
#include "Physics.h"
#include <math.h>
#include <Windows.h>

const float Robot::AccelRate = 9.1;
const float Robot::DecelRate = 6.9;
const float Robot::MaxSpeed = 8.6;

const float Robot::BaseMaxAngularVelocity = M_PI / 2;
const float Robot::UpperArmMaxAngularVelocity = M_PI / 4;
const float Robot::LowerArmMaxAngularVelocity = M_PI / 4;

float Robot::RobotShoulderJointRadius = 0.125;
float Robot::RobotElbowJointRadius = 0.1;
float Robot::RobotWristJointRadius = 0.069;
ColorRGB Robot::RobotJointColor = ColorRGB(0, 184, 212);
float Robot::RobotBaseRadius = 0.5;
ColorRGB Robot::RobotBaseColor = ColorRGB(48, 79, 254);
float Robot::RobotUpperArmRadius = 0.069;
float Robot::RobotUpperArmLength = 0.69;
ColorRGB Robot::RobotUpperArmColor = ColorRGB(100, 221, 23);
float Robot::RobotLowerArmRadius = 0.05;
float Robot::RobotLowerArmLength = 0.5;
ColorRGB Robot::RobotLowerArmColor = ColorRGB(255, 171, 0);

Robot::Robot() {
	saved = { Vector3f::Zero(), 0, Vector3f::Zero(), Vector3f::Zero(), 0, 0, 0 };
	current = { Vector3f::Zero(), 0, Vector3f::Zero(), Vector3f::Zero(), 0, 0, 0 };
}

Robot::~Robot()
{
}

void Robot::moveBase(int direction) {
	positionInputTimer = Input::InputDelay / 1000;
	current.acceleration = AccelRate * Vector3f(direction * cos(current.baseAngle), 0, direction * sin(current.baseAngle)).unitVector();
}

void Robot::rotateBase(int direction) {
	baseAngleInputTimer = Input::InputDelay / 1000;
	if (direction)
		baseAngularVelocity = direction / abs(direction) * BaseMaxAngularVelocity;
}

void Robot::moveUpperArm(int direction) {
	upperArmAngleInputTimer = Input::InputDelay / 1000;
	if (direction)
		upperArmAngularVelocity = direction / abs(direction) * UpperArmMaxAngularVelocity;
}

void Robot::moveLowerArm(int direction) {
	lowerArmAngleInputTimer = Input::InputDelay / 1000;
	if (direction)
		lowerArmAngularVelocity = direction / abs(direction) * LowerArmMaxAngularVelocity;
}

void Robot::updatePosition(Vector3f& position, Vector3f& velocity) {
	current.position = position;
	current.velocity = min(velocity.getMagnitude(), MaxSpeed) * velocity.unitVector();
}

void Robot::updateTimer(float delta) {
	positionInputTimer = max(positionInputTimer - delta, 0.0f);
	baseAngleInputTimer = max(baseAngleInputTimer - delta, 0.0f);
	upperArmAngleInputTimer = max(upperArmAngleInputTimer - delta, 0.0f);
	lowerArmAngleInputTimer = max(lowerArmAngleInputTimer - delta, 0.0f);
}

void Robot::updateState() {

	// Update base position.
	if (positionInputTimer > 0) {
		// Do something.
	}
	else {
		if (current.velocity.getMagnitude() > 0) {
			Vector3f newAcceleration = -DecelRate * current.velocity.unitVector();
			if (!(Vector3f::Dot(newAcceleration, current.velocity) < 1.0f)) {
				current.velocity = Vector3f::Zero();
				current.acceleration = Vector3f::Zero();
			}
			else {
				current.acceleration = newAcceleration;
			}
		}
	}

	// Update base angle.
	if (baseAngleInputTimer > 0) {
		current.baseAngle += baseAngularVelocity * Physics::DeltaTime;
		// Wrap angle between 0 to 360 degrees.
		// This assumes that each update, the angle does not change more than 360 degrees.
		if (current.baseAngle > 2 * M_PI) {
			current.baseAngle -= 2 * M_PI;
		}
		else if (current.baseAngle < 0) {
			current.baseAngle += 2 * M_PI;;
		}
	}
	else {
		baseAngularVelocity = 0;
	}

	// Update upper arm angle.
	if (upperArmAngleInputTimer > 0) {
		current.upperArmAngle = min(max(current.upperArmAngle + upperArmAngularVelocity * Physics::DeltaTime, -0.375 * M_PI), 0.375 * M_PI);
	}
	else {
		upperArmAngularVelocity = 0;
	}

	// Update lower arm angle.
	if (lowerArmAngleInputTimer > 0) {
		current.lowerArmAngle += lowerArmAngularVelocity * Physics::DeltaTime;
		// Wrap angle between 0 to 360 degrees.
		// This assumes that each update, the angle does not change more than 360 degrees.
		if (current.lowerArmAngle > 2 * M_PI) {
			current.lowerArmAngle -= 2 * M_PI;
		}
		else if (current.lowerArmAngle < 0) {
			current.lowerArmAngle += 2 * M_PI;;
		}
	}
	else {
		lowerArmAngularVelocity = 0;
	}

}

RobotState& Robot::getCurrentState() {
	return current;
}
