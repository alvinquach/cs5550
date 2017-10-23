// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#include "Physics.h"
#include <iostream>

using std::cout;

const int Physics::UpdatesPerFrame = 10;

// This is calculated from UpdateRate.
const double Physics::DeltaTime = 1.0 / (UpdatesPerFrame * Window::FrameRate);

const float Physics::RobotWorldCollisionSlowDownFactor = 0.5;
const float Physics::BallWorldCollisionSlowDownFactor = 0.91;

void Physics::Update() {
	Robot& robot = Scene::GetRobot();
	robot.updateTimer(DeltaTime);

	RobotState& robotState = robot.getCurrentState();
	Vector3f& newVelocity = robotState.velocity + DeltaTime * robotState.acceleration;
	CheckWorldCollision(false, Robot::RobotBaseRadius, robotState.position, newVelocity, RobotWorldCollisionSlowDownFactor);
	Vector3f& newPosition = robotState.position + DeltaTime * newVelocity;
	robot.updatePosition(newPosition, newVelocity);
	robot.updateState();

	UpdateBalls();
}

void Physics::UpdateBalls() {

	// Get balls from scene.
	vector<Ball>& balls = Scene::GetInstance().GetBalls();

	// Balls marked for deletion.
	vector<int> markForDelete;

	// Update position based on velocity, and then check for collision with world.
	for (int i = 0; i < balls.size(); i++) {
		Ball& ball = balls[i];
		UpdateBallPosition(ball);
		bool test = CheckWorldCollision(true, Ball::Radius, ball.getPosition(), ball.getVelocity(), BallWorldCollisionSlowDownFactor);
		if (ball.getPosition().getY() < Ball::Radius + 0.001) {
			if (abs(ball.getVelocity().getY()) < 0.5) {
				ball.getVelocity().setY(0.0);
				markForDelete.push_back(i);
			}
		}
		else {
			ApplyGravityToBall(ball);
		}
	}

	for (int i = 0; i < markForDelete.size(); i++) {
		balls.erase(balls.begin() + markForDelete[i]);
	}

}

void Physics::UpdateBallPosition(Ball& ball) {
	ball.setPosition(ball.getPosition() + DeltaTime * ball.getVelocity());
}

void Physics::ApplyGravityToBall(Ball& ball) {
	ball.setVelocity(ball.getVelocity() + Vector3f(0, -9.8 * DeltaTime, 0));
}

bool Physics::CheckWorldCollision(bool checkVertical, float radius, Vector3f& position, Vector3f& velocity, float slowDownFactor) {

	bool collided = false;

	if (position.getZ() > Scene::GetRoomDimensions().getZ() / 2 - radius) {
		position.setZ(Scene::GetRoomDimensions().getZ() / 2 - radius);
		velocity.reflect(Vector3f::Back());
		collided = true;
	}

	if (position.getX() > Scene::GetRoomDimensions().getX() / 2 - radius) {
		position.setX(Scene::GetRoomDimensions().getX() / 2 - radius);
		velocity.reflect(Vector3f::Left());
		collided = true;
	}

	if (position.getZ() < radius - Scene::GetRoomDimensions().getZ() / 2) {
		position.setZ(radius - Scene::GetRoomDimensions().getZ() / 2);
		velocity.reflect(Vector3f::Forward());
		collided = true;
	}

	if (position.getX() < radius - Scene::GetRoomDimensions().getX() / 2) {
		position.setX(radius - Scene::GetRoomDimensions().getX() / 2);
		velocity.reflect(Vector3f::Right());
		collided = true;
	}

	if (checkVertical) {
		if (position.getY() > Scene::GetRoomDimensions().getY() - radius) {
			position.setY(Scene::GetRoomDimensions().getY() - radius);
			velocity.reflect(Vector3f::Down());
			collided = true;
		}
		if (position.getY() < 0) {
			position.setY(radius);
			velocity.reflect(Vector3f::Up());
			collided = true;
		}
	}

	// Reduce the velocity after collision.
	if (collided) {
		velocity.scale(slowDownFactor);
	}

	return collided;

}
