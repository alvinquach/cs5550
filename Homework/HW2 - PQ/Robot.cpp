#include "Robot.h"
#include <algorithm>

using std::max;

const float Robot::AccelRate = 5;
const float Robot::DecelRate = 5;

Robot::Robot() {
	saved = { Vector3f::Zero(), 0, Vector3f::Zero(), Vector3f::Zero(), 0, 0, 0 };
	current = { Vector3f::Zero(), 0, Vector3f::Zero(), Vector3f::Zero(), 0, 0, 0 };
	positionInputTimer = 0;
	baseAngleInputTimer = 0;
}

Robot::~Robot()
{
}

void Robot::moveForward() {
	positionInputTimer = Input::InputDelay;
}

void Robot::moveBackward() {
	positionInputTimer = Input::InputDelay;
}

void Robot::updatePosition(Vector3f& position, float angle, Vector3f, Vector3f velocity) {
	current.position = position;
	current.baseAngle = angle;
	current.velocity = velocity;
}

void Robot::updateTimer(float delta) {
	positionInputTimer = max(positionInputTimer - delta, 0.0f);
	baseAngleInputTimer = max(baseAngleInputTimer - delta, 0.0f);

	if (positionInputTimer == 0)
		current.acceleration = Vector3f::Zero();
}

RobotState& Robot::getCurrentState() {
	return current;
}
