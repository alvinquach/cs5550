// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

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

const float Robot::UpperArmMinAngle = -M_PI * 3 / 8;
const float Robot::UpperArmMaxAngle = M_PI * 3 / 8;
const float Robot::LowerArmMinAngle = 0.0;
const float Robot::LowerArmMaxAngle = M_PI / 2;
const float Robot::HandMinAngle = -M_PI / 8;
const float Robot::HandMaxAngle = M_PI / 2;
const float Robot::FingerMinAngle = M_PI / 16;
const float Robot::FingerMaxAngle = M_PI * 9 / 16;
const float Robot::ThumbMinAngle = M_PI / 96;
const float Robot::ThumbMaxAngle = M_PI * 9 / 96;

float Robot::RobotShoulderJointRadius = 0.125;
float Robot::RobotElbowJointRadius = 0.1;
float Robot::RobotWristJointRadius = 0.069;
ColorRGB Robot::RobotJointColor = ColorRGB(98, 0, 234);

float Robot::RobotBaseRadius = 0.5;
ColorRGB Robot::RobotBaseColor = ColorRGB(197, 17, 98);

float Robot::RobotUpperArmRadius = 0.069;
float Robot::RobotUpperArmLength = 0.69;
ColorRGB Robot::RobotUpperArmColor = ColorRGB(255, 109, 0);

float Robot::RobotLowerArmRadius = 0.05;
float Robot::RobotLowerArmLength = 0.5;
ColorRGB Robot::RobotLowerArmColor = ColorRGB(255, 214, 0);

float Robot::HandLength = 0.25;
float Robot::HandThickness = 0.025;
ColorRGB Robot::HandColor = ColorRGB(174, 234, 0);

float Robot::FingerProximalDigitLength = 0.1;
float Robot::FingerProximalDigitThickness = 0.02;
ColorRGB Robot::FingerProximalDigitColor = ColorRGB(0, 200, 83);

float Robot::FingerMiddleDigitLength = 0.08;
float Robot::FingerMiddleDigitThickness = 0.0175;
ColorRGB Robot::FingerMiddleDigitColor = ColorRGB(0, 184, 212);

float Robot::FingerDistalDigitLength = 0.05;
float Robot::FingerDistalDigitThickness = 0.015;
ColorRGB Robot::FingerDistalDigitColor = ColorRGB(48, 79, 254);

float Robot::FingerScale[4] = { 0.91, 1.0, 0.95, 0.83 };

float Robot::ThumbProximalDigitLength = 0.08;
float Robot::ThumbProximalDigitThickness = 0.02;
ColorRGB Robot::ThumbProximalDigitColor = ColorRGB(0, 200, 83);

float Robot::ThumbDistalDigitLength = 0.06;
float Robot::ThumbDistalDigitThickness = 0.02;
ColorRGB Robot::ThumbDistalDigitColor = ColorRGB(48, 79, 254);

const RobotState Robot::ThrowPrepState = {
	Vector3f::Zero(),
	0.0,
	Vector3f::Zero(),
	Vector3f::Zero(),
	-M_PI / 4,
	LowerArmMinAngle,
	HandMinAngle,
	M_PI / 4,
	M_PI / 24
};

const RobotState Robot::ThrowingState = {
	Vector3f::Zero(),
	0.0,
	Vector3f::Zero(),
	Vector3f::Zero(),
	-M_PI / 8,
	M_PI / 8,
	0.0,
	FingerMinAngle,
	ThumbMinAngle
};

Robot::Robot() {
	saved = { Vector3f::Zero(), 0, Vector3f::Zero(), Vector3f::Zero(), 0, 0, 0, Robot::FingerMinAngle, Robot::ThumbMinAngle };
	current = { Vector3f::Zero(), 0, Vector3f::Zero(), Vector3f::Zero(), 0, 0, 0, Robot::FingerMinAngle, Robot::ThumbMinAngle };
}

Robot::~Robot()
{
}

void Robot::moveBase(int direction) {
	if (disabled) {
		return;
	}
	positionInputTimer = Input::InputDelay / 1000;
	current.acceleration = AccelRate * Vector3f(direction * cos(current.baseAngle), 0, direction * sin(current.baseAngle)).unitVector();
}

void Robot::rotateBase(int direction) {
	if (disabled) {
		return;
	}
	baseAngleInputTimer = Input::InputDelay / 1000;
	if (direction)
		baseAngularVelocity = direction / abs(direction) * BaseMaxAngularVelocity;
}

void Robot::moveUpperArm(int direction) {
	if (disabled || throwing) {
		return;
	}
	upperArmAngleInputTimer = Input::InputDelay / 1000;
	if (direction)
		upperArmAngularVelocity = direction / abs(direction) * UpperArmMaxAngularVelocity;
}

void Robot::moveLowerArm(int direction) {
	if (disabled || throwing) {
		return;
	}
	lowerArmAngleInputTimer = Input::InputDelay / 1000;
	if (direction)
		lowerArmAngularVelocity = direction / abs(direction) * LowerArmMaxAngularVelocity;
}

void Robot::moveHand(int direction) {
	if (disabled || throwing) {
		return;
	}
	handAngleInputTimer = Input::InputDelay / 1000;
	if (direction)
		handAngularVelocity = direction / abs(direction) * HandMaxAngularVelocity;
}

void Robot::moveFingers(int direction) {
	if (disabled || throwing) {
		return;
	}
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

	// Only move arm if it is not throwing.
	if (!throwing) {

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

	// If arm is throwing, update the throwing animation instead.
	else {

		// Prep the arm for throwing.
		if (!readyToThrow) {

			int readyCount = 0;

			// Upper Arm
			if (current.upperArmAngle < ThrowPrepState.upperArmAngle) {
				current.upperArmAngle = min(current.upperArmAngle + UpperArmMaxAngularVelocity * Physics::DeltaTime, ThrowPrepState.upperArmAngle);
			}
			else if (current.upperArmAngle > ThrowPrepState.upperArmAngle) {
				current.upperArmAngle = max(current.upperArmAngle - UpperArmMaxAngularVelocity * Physics::DeltaTime, ThrowPrepState.upperArmAngle);
			}
			if (current.upperArmAngle == ThrowPrepState.upperArmAngle) {
				readyCount++;
			}

			// Lower Arm
			if (current.lowerArmAngle < ThrowPrepState.lowerArmAngle) {
				current.lowerArmAngle = min(current.lowerArmAngle + LowerArmMaxAngularVelocity * Physics::DeltaTime, ThrowPrepState.lowerArmAngle);
			}
			else if (current.lowerArmAngle > ThrowPrepState.lowerArmAngle) {
				current.lowerArmAngle = max(current.lowerArmAngle - LowerArmMaxAngularVelocity * Physics::DeltaTime, ThrowPrepState.lowerArmAngle);
			}
			if (current.lowerArmAngle == ThrowPrepState.lowerArmAngle) {
				readyCount++;
			}

			// Hand
			if (current.handAngle < ThrowPrepState.handAngle) {
				current.handAngle = min(current.handAngle + HandMaxAngularVelocity * Physics::DeltaTime, ThrowPrepState.handAngle);
			}
			else if (current.handAngle > ThrowPrepState.handAngle) {
				current.handAngle = max(current.handAngle - HandMaxAngularVelocity * Physics::DeltaTime, ThrowPrepState.handAngle);
			}
			if (current.handAngle == ThrowPrepState.handAngle) {
				readyCount++;
			}

			// Fingers
			if (current.fingerAngle < ThrowPrepState.fingerAngle) {
				current.fingerAngle = min(current.fingerAngle + FingerMaxAngularVelocity * Physics::DeltaTime, ThrowPrepState.fingerAngle);
			}
			else if (current.fingerAngle > ThrowPrepState.fingerAngle) {
				current.fingerAngle = max(current.fingerAngle - FingerMaxAngularVelocity * Physics::DeltaTime, ThrowPrepState.fingerAngle);
			}
			if (current.fingerAngle == ThrowPrepState.fingerAngle) {
				readyCount++;
			}

			// Thumb
			if (current.thumbAngle < ThrowPrepState.thumbAngle) {
				current.thumbAngle = min(current.thumbAngle + ThumbMaxAngularVelocity * Physics::DeltaTime, ThrowPrepState.thumbAngle);
			}
			else if (current.thumbAngle > ThrowPrepState.thumbAngle) {
				current.thumbAngle = max(current.thumbAngle - ThumbMaxAngularVelocity * Physics::DeltaTime, ThrowPrepState.thumbAngle);
			}
			if (current.thumbAngle == ThrowPrepState.thumbAngle) {
				readyCount++;
			}

			if (readyCount == 5) {
				readyToThrow = true;
				throwCountdown = 100;
			}
		}

		// Countdown to start throwing.
		else if (throwCountdown) {
			throwCountdown--;
		}

		// ITHROWPOWER
		else {
			int delay = 69;
			current.upperArmAngle += (ThrowingState.upperArmAngle - ThrowPrepState.upperArmAngle) / delay;
			current.lowerArmAngle += (ThrowingState.lowerArmAngle - ThrowPrepState.lowerArmAngle) / delay;
			current.handAngle += (ThrowingState.handAngle - ThrowPrepState.handAngle) / delay;
			current.fingerAngle += (ThrowingState.fingerAngle - ThrowPrepState.fingerAngle) / delay;
			current.thumbAngle += (ThrowingState.thumbAngle - ThrowPrepState.thumbAngle) / delay;
			throwProgress++;
			if (throwProgress >= delay) {
				throwing = false;
				readyToThrow = false;
				throwProgress = 0;
				Scene::LaunchBall(
					current.position + Vector3f(-0.3, 1.4, 0),
					7.25 * Vector3f(cos(current.baseAngle), 0, sin(current.baseAngle)) + current.velocity
				);
			}
		}

	}

}

RobotState& Robot::getCurrentState() {
	return current;
}


void Robot::disable() {
	disabled = true;
}

void Robot::enable() {
	disabled = false;
}

bool Robot::isDisabled() {
	return disabled;
}

bool Robot::isThrowing() {
	return throwing;
}

void Robot::iThrowPower() {
	throwing = true;

	// Reset arm angular velocities.
	upperArmAngularVelocity
		= lowerArmAngularVelocity
		= handAngularVelocity
		= fingerAngularVelocity
		= thumbAngularVelocity
		= 0;

	readyToThrow = false;
	throwProgress = 0;
}

bool Robot::isHoldingBall() {
	return throwing && readyToThrow;
}

// This is currently not being used.
void Robot::saveState(RobotState state) {
	saved = {
		state.position,
		state.baseAngle,
		state.velocity,
		state.acceleration,
		state.upperArmAngle,
		state.lowerArmAngle,
		state.handAngle,
		state.fingerAngle,
		state.thumbAngle,
	};
}

// This is currently not being used.
void Robot::applyState(RobotState& state) {

}
