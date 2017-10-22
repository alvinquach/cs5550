#include "Physics.h"
#include <iostream>

using std::cout;

const int Physics::UpdatesPerFrame = 10;


// This is calculated from UpdateRate.
const double Physics::DeltaTime = 1.0 / (UpdatesPerFrame * Window::FrameRate);

void Physics::Update() {
	Robot& robot = Scene::GetRobot();
	robot.updateTimer(DeltaTime);

	RobotState& robotState = robot.getCurrentState();
	Vector3f newPosition = robotState.position + DeltaTime * robotState.velocity;
	Vector3f newVelocity = robotState.velocity + DeltaTime * robotState.acceleration;

	// cout << "(" << robotState.acceleration.getX() << ", " << robotState.acceleration.getZ() << ")" << endl;

	robot.updatePosition(newPosition, newVelocity);
	robot.updateState();
}