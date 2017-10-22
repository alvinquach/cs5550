#define _USE_MATH_DEFINES
#include "Robot.h"
#include "Physics.h"
#include <math.h>
#include <Windows.h>

const float Robot::AccelRate = 13.37;
const float Robot::DecelRate = 6.9;
const float Robot::MaxSpeed = 4.20;

const float Robot::BaseMaxAngularVelocity = M_PI / 2;

Robot::Robot() {
	saved = { Vector3f::Zero(), 0, Vector3f::Zero(), Vector3f::Zero(), 0, 0, 0 };
	current = { Vector3f::Zero(), 0, Vector3f::Zero(), Vector3f::Zero(), 0, 0, 0 };
	positionInputTimer = 0;
	baseAngleInputTimer = 0;
}

Robot::~Robot()
{
}

void Robot::move(int direction) {
	positionInputTimer = Input::InputDelay / 1000;
	current.acceleration = AccelRate * Vector3f(direction * cos(current.baseAngle), 0, direction * sin(current.baseAngle)).unitVector();
}

void Robot::rotateBase(int direction) {
	baseAngleInputTimer = Input::InputDelay / 1000;
	if (direction)
		baseAngularVelocity = direction / abs(direction) * BaseMaxAngularVelocity;
}

void Robot::updatePosition(Vector3f& position, Vector3f& velocity) {
	current.position = position;
	current.velocity = min(velocity.getMagnitude(), MaxSpeed) * velocity.unitVector();
}

void Robot::updateTimer(float delta) {
	positionInputTimer = max(positionInputTimer - delta, 0.0f);
	baseAngleInputTimer = max(baseAngleInputTimer - delta, 0.0f);
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
}

RobotState& Robot::getCurrentState() {
	return current;
}
