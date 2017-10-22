#include "Physics.h"
#include <iostream>

using std::cout;

const int Physics::UpdatesPerFrame = 10;


// This is calculated from UpdateRate.
const double Physics::DeltaTime = 1.0 / (UpdatesPerFrame * Window::FrameRate);

void CheckRobotBaseWorldCollision(Vector3f& velocity) {

	float radius = Robot::RobotBaseRadius;
	Vector3f position = Scene::GetRobot().getCurrentState().position;

	if (position.getZ() >= Scene::GetRoomDimensions().getZ() / 2 - radius) {
		position.setZ(Scene::GetRoomDimensions().getZ() / 2 - radius);
		velocity.reflect(Vector3f::Back());
	}

	if (position.getX() >= Scene::GetRoomDimensions().getX() / 2 - radius) {
		position.setX(Scene::GetRoomDimensions().getX() / 2 - radius);
		velocity.reflect(Vector3f::Left());
	}

	if (position.getZ() <= radius - Scene::GetRoomDimensions().getZ() / 2) {
		position.setZ(radius - Scene::GetRoomDimensions().getZ() / 2);
		velocity.reflect(Vector3f::Forward());
	}

	if (position.getX() <= radius - Scene::GetRoomDimensions().getX() / 2) {
		position.setX(radius - Scene::GetRoomDimensions().getX() / 2);
		velocity.reflect(Vector3f::Right());
	}

}

void Physics::Update() {
	Robot& robot = Scene::GetRobot();
	robot.updateTimer(DeltaTime);

	RobotState& robotState = robot.getCurrentState();
	Vector3f& newVelocity = robotState.velocity + DeltaTime * robotState.acceleration;
	CheckRobotBaseWorldCollision(newVelocity);
	Vector3f& newPosition = robotState.position + DeltaTime * newVelocity;
	robot.updatePosition(newPosition, newVelocity);
	robot.updateState();
}

