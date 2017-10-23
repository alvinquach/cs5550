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
	float fingerAngle;
	float thumbAngle;
	//float fingerProximalDigitAngle;
	//float fingerMiddleDigitAngle;
	//float fingerDistalDigitAngle; 
	//float thumbProximalDigitAngle;
	//float thumbDistalDigitAngle;
};

class Robot {
public:
	static float RobotShoulderJointRadius;
	static float RobotElbowJointRadius;
	static float RobotWristJointRadius;
	static float RobotFingerJointRadius;
	static ColorRGB RobotJointColor;

	static float RobotBaseRadius;
	static ColorRGB RobotBaseColor;

	static float RobotUpperArmRadius;
	static float RobotUpperArmLength;
	static ColorRGB RobotUpperArmColor;

	static float RobotLowerArmRadius;
	static float RobotLowerArmLength;
	static ColorRGB RobotLowerArmColor;

	static float HandLength;
	static float HandThickness;
	static ColorRGB HandColor;

	static float FingerProximalDigitLength;
	static float FingerProximalDigitThickness;
	static ColorRGB FingerProximalDigitColor;

	static float FingerMiddleDigitLength;
	static float FingerMiddleDigitThickness;
	static ColorRGB FingerMiddleDigitColor;

	static float FingerDistalDigitLength;
	static float FingerDistalDigitThickness;
	static ColorRGB FingerDistalDigitColor;

	static float FingerScale[4];

	static float ThumbProximalDigitLength;
	static float ThumbProximalDigitThickness;
	static ColorRGB ThumbProximalDigitColor;

	static float ThumbDistalDigitLength;
	static float ThumbDistalDigitThickness;
	static ColorRGB ThumbDistalDigitColor;
	Robot();
	~Robot();

	void moveBase(int direction);
	void rotateBase(int direction);
	void moveUpperArm(int direction);
	void moveLowerArm(int direction);
	void moveHand(int direction);
	void moveFingers(int direction);

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
	static const float HandMaxAngularVelocity;
	static const float FingerMaxAngularVelocity;
	static const float ThumbMaxAngularVelocity;

	//static const float FingerProximalDigitMaxAngularVelocity;
	//static const float FingerMiddleDigitMaxAngularVelocity;
	//static const float FingerDistalDigitMaxAngularVelocity;
	//static const float ThumbProximalDigitMaxAngularVelocity;
	//static const float ThumbDistalDigitMaxAngularVelocity;

	static const float UpperArmMinAngle;
	static const float UpperArmMaxAngle;
	static const float LowerArmMinAngle;
	static const float LowerArmMaxAngle;
	static const float HandMinAngle;
	static const float HandMaxAngle;
	static const float FingerMinAngle;
	static const float FingerMaxAngle;
	static const float ThumbMinAngle;
	static const float ThumbMaxAngle;

	float positionInputTimer;
	float baseAngleInputTimer;
	float upperArmAngleInputTimer;
	float lowerArmAngleInputTimer;
	float handAngleInputTimer;
	float fingerAngleInputTimer;

	float baseAngularVelocity;
	float upperArmAngularVelocity;
	float lowerArmAngularVelocity;
	float handAngularVelocity;
	float fingerAngularVelocity;
	float thumbAngularVelocity;

	//float fingerProximalDigitAngularVelocity;
	//float fingerMiddleDigitAngularVelocity;
	//float fingerDistalDigitAngularVelocity;
	//float thumbProximalDigitAngularVelocity;
	//float thumbDistalDigitAngularVelocity;

	Vector3f positionSpeed;

	RobotState current;
	RobotState saved;
};

