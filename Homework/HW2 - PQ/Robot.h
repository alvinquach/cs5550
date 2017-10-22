#pragma once
#include "Vector3f.h"
#include "Window.h"
#include "Input.h"

struct RobotState {
	Vector3f position;
	float baseAngle;
	Vector3f velocity;
	Vector3f acceleration;
	float upperArmAngle;
	float lowerArmAngle;
	float handAngle;
};

class Robot {
public:
	Robot();
	~Robot();
	void moveForward();
	void moveBackward();
	void updatePosition(Vector3f& position, float angle, Vector3f, Vector3f velocity);
	void updateTimer(float delta);
	RobotState& getCurrentState();

private:
	static const float AccelRate;
	static const float DecelRate;

	float positionLerp;
	float rotationLerp;

	float positionInputTimer;
	float baseAngleInputTimer;

	Vector3f positionSpeed;
	float rotationSpeed;

	RobotState current;
	RobotState saved;
};

