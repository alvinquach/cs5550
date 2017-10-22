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
	void move(int direction);
	void rotateBase(int direction);
	void updatePosition(Vector3f& position, Vector3f& velocity);
	void updateTimer(float delta);
	void updateState();
	RobotState& getCurrentState();

private:

	static const float AccelRate;
	static const float DecelRate;
	static const float MaxSpeed;

	static const float BaseMaxAngularVelocity;

	float positionInputTimer;
	float baseAngleInputTimer;

	float baseAngularVelocity;

	Vector3f positionSpeed;
	float rotationSpeed;

	RobotState current;
	RobotState saved;
};

