#pragma once
#include "Vector3f.h"
#include "Window.h"
#include "Input.h"
#include "ColorRGB.h"

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
	static float RobotShoulderJointRadius;
	static float RobotElbowJointRadius;
	static float RobotWristJointRadius;
	static ColorRGB RobotJointColor;
	static float RobotBaseRadius;
	static ColorRGB RobotBaseColor;
	static float RobotUpperArmRadius;
	static float RobotUpperArmLength;
	static ColorRGB RobotUpperArmColor;
	static float RobotLowerArmRadius;
	static float RobotLowerArmLength;
	static ColorRGB RobotLowerArmColor;
	Robot();
	~Robot();

	void moveBase(int direction);
	void rotateBase(int direction);
	void moveUpperArm(int direction);
	void moveLowerArm(int direction);

	void updatePosition(Vector3f& position, Vector3f& velocity);
	void updateTimer(float delta);
	void updateState();
	RobotState& getCurrentState();

private:

	static const float AccelRate;
	static const float DecelRate;
	static const float MaxSpeed;

	static const float BaseMaxAngularVelocity;
	static const float UpperArmMaxAngularVelocity;
	static const float LowerArmMaxAngularVelocity;

	float positionInputTimer;
	float baseAngleInputTimer;
	float upperArmAngleInputTimer;
	float lowerArmAngleInputTimer;

	float baseAngularVelocity;
	float upperArmAngularVelocity;
	float lowerArmAngularVelocity;

	Vector3f positionSpeed;
	float rotationSpeed;

	RobotState current;
	RobotState saved;
};

