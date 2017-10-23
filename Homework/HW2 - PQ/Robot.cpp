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
const float Robot::HandMaxAngularVelocity = M_PI / 4;
const float Robot::FingerMaxAngularVelocity = M_PI / 4;
const float Robot::ThumbMaxAngularVelocity = M_PI / 24;

const float Robot::UpperArmMinAngle = - M_PI * 3 / 8;
const float Robot::UpperArmMaxAngle = M_PI * 3 / 8;
const float Robot::LowerArmMinAngle = 0.0;
const float Robot::LowerArmMaxAngle = M_PI / 2;
const float Robot::HandMinAngle = - M_PI / 8;
const float Robot::HandMaxAngle = M_PI / 2;
const float Robot::FingerMinAngle = M_PI / 16;
const float Robot::FingerMaxAngle = M_PI * 9 / 16;
const float Robot::ThumbMinAngle = M_PI / 96;
const float Robot::ThumbMaxAngle = M_PI * 9 / 96;

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

float Robot::HandLength = 0.25;
float Robot::HandThickness = 0.025;
ColorRGB Robot::HandColor = ColorRGB(221, 44, 0);

float Robot::FingerProximalDigitLength = 0.1;
float Robot::FingerProximalDigitThickness = 0.02;
ColorRGB Robot::FingerProximalDigitColor = ColorRGB(197, 17, 98);

float Robot::FingerMiddleDigitLength = 0.08;
float Robot::FingerMiddleDigitThickness = 0.0175;
ColorRGB Robot::FingerMiddleDigitColor = ColorRGB(98, 0, 234);

float Robot::FingerDistalDigitLength = 0.05;
float Robot::FingerDistalDigitThickness = 0.015;
ColorRGB Robot::FingerDistalDigitColor = ColorRGB(41, 98, 255);

float Robot::FingerScale[4] = { 0.91, 1.0, 0.95, 0.83 };

float Robot::ThumbProximalDigitLength = 0.08;
float Robot::ThumbProximalDigitThickness = 0.02;
ColorRGB Robot::ThumbProximalDigitColor = ColorRGB(0, 184, 212);

float Robot::ThumbDistalDigitLength = 0.06;
float Robot::ThumbDistalDigitThickness = 0.02;
ColorRGB Robot::ThumbDistalDigitColor = ColorRGB(0, 200, 83);

Robot::Robot() {
	saved = { Vector3f::Zero(), 0, Vector3f::Zero(), Vector3f::Zero(), 0, 0, 0, Robot::FingerMinAngle, Robot::ThumbMinAngle };
	current = { Vector3f::Zero(), 0, Vector3f::Zero(), Vector3f::Zero(), 0, 0, 0, Robot::FingerMinAngle, Robot::ThumbMinAngle };
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

void Robot::moveHand(int direction) {
	handAngleInputTimer = Input::InputDelay / 1000;
	if (direction)
		handAngularVelocity = direction / abs(direction) * HandMaxAngularVelocity;
}

void Robot::moveFingers(int direction) {
	fingerAngleInputTimer = Input::InputDelay / 1000;
	if (direction) {
		fingerAngularVelocity = direction / abs(direction) * FingerMaxAngularVelocity;
		thumbAngularVelocity = direction / abs(direction) * ThumbMaxAngularVelocity;
	}
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
	handAngleInputTimer = max(handAngleInputTimer - delta, 0.0f);
	fingerAngleInputTimer = max(fingerAngleInputTimer - delta, 0.0f);
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
		current.upperArmAngle = min(max(current.upperArmAngle + upperArmAngularVelocity * Physics::DeltaTime, UpperArmMinAngle), UpperArmMaxAngle);
	}
	else {
		upperArmAngularVelocity = 0;
	}

	// Update lower arm angle.
	if (lowerArmAngleInputTimer > 0) {
		current.lowerArmAngle = min(max(current.lowerArmAngle + lowerArmAngularVelocity * Physics::DeltaTime, LowerArmMinAngle), LowerArmMaxAngle);
	}
	else {
		lowerArmAngularVelocity = 0;
	}

	// Check lower arm angle constraints relative to upper arm.
	if (current.lowerArmAngle + current.upperArmAngle > LowerArmMaxAngle) {
		current.lowerArmAngle = LowerArmMaxAngle - current.upperArmAngle;
	}

	// Update hand angle.
	if (handAngleInputTimer > 0) {
		current.handAngle = min(max(current.handAngle + handAngularVelocity * Physics::DeltaTime, HandMinAngle), HandMaxAngle);
	}
	else {
		handAngularVelocity = 0;
	}

	// Update fingers angle.
	if (fingerAngleInputTimer > 0) {
		current.fingerAngle = min(max(current.fingerAngle + fingerAngularVelocity * Physics::DeltaTime, FingerMinAngle), FingerMaxAngle);
		current.thumbAngle = min(max(current.thumbAngle + thumbAngularVelocity * Physics::DeltaTime, ThumbMinAngle), ThumbMaxAngle);
	}
	else {
		fingerAngularVelocity = thumbAngularVelocity = 0;
	}

}

RobotState& Robot::getCurrentState() {
	return current;
}
