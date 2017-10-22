#include "Physics.h"
#include <iostream>

using std::cout;

const int Physics::UpdatesPerFrame = 10;


// This is calculated from UpdateRate.
const double Physics::DeltaTime = 1.0 / (UpdatesPerFrame * Window::FrameRate);

void CheckRobotBaseWorldCollision() {

	float radius = Robot::RobotBaseRadius;
	RobotState& robotState = Scene::GetRobot().getCurrentState();

	if (robotState.position.getZ() >= Scene::GetRoomDimensions().getZ() / 2 - radius) {
		robotState.position.setZ(Scene::GetRoomDimensions().getZ() / 2 - radius);
		robotState.velocity.reflect(Vector3f::Down());
	}

	if (robotState.position.getX() >= Scene::GetRoomDimensions().getX() / 2 - radius) {
		robotState.position.setX(Scene::GetRoomDimensions().getX() / 2 - radius);
		robotState.velocity.reflect(Vector3f::Left());
	}

	if (robotState.position.getZ() <= radius - Scene::GetRoomDimensions().getZ() / 2) {
		robotState.position.setZ(radius - Scene::GetRoomDimensions().getZ() / 2);
		robotState.velocity.reflect(Vector3f::Up());
	}

	if (robotState.position.getX() <= radius - Scene::GetRoomDimensions().getX() / 2) {
		robotState.position.setX(radius - Scene::GetRoomDimensions().getX() / 2);
		robotState.velocity.reflect(Vector3f::Right());
	}

}

void Physics::Update() {
	Robot& robot = Scene::GetRobot();
	robot.updateTimer(DeltaTime);

	RobotState& robotState = robot.getCurrentState();
	Vector3f newPosition = robotState.position + DeltaTime * robotState.velocity;
	Vector3f newVelocity = robotState.velocity + DeltaTime * robotState.acceleration;
	CheckRobotBaseWorldCollision();

	// cout << "(" << robotState.acceleration.getX() << ", " << robotState.acceleration.getZ() << ")" << endl;

	robot.updatePosition(newPosition, newVelocity);
	robot.updateState();
}

