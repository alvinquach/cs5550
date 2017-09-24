#include "Physics.h"
#include "Scene.h"
#include <windows.h>
#include <iostream>

const int Physics::UpdatesPerFrame = 10;

// This is calculated from UpdateRate.
const double Physics::DeltaTime = 1.0 / (UpdatesPerFrame * frameRate);

void Physics::UpdateBalls() {

	// Get balls from scene.
	vector<Ball>& balls = Scene::GetInstance().GetBalls();

	// Update position based on velocity, and then check for collision with world.
	for (vector<Ball>::iterator ball = balls.begin(); ball != balls.end(); ++ball) {
		UpdateBallPosition(*ball);
		CheckBallWorldCollision(*ball);
	}

	// Check and update solidity status of balls.
	CheckBallSolidity(balls);

	// Check for collision against other balls.
	for (int i = 0; i < balls.size() - 1; i++) {
		Ball& a = balls[i];
		for (int j = i + 1; j < balls.size(); j++) {
			Ball& b = balls[j];

			// Skip the ball if it's not solid.
			if (!b.isSolid()) {
				continue;
			}

			if (BallsCollided(a, b)) {
				if (i == Scene::GetLockedBallIndex()) {
					HandleLockedBallCollision(a, b);
				}
				else if (j == Scene::GetLockedBallIndex()) {
					HandleLockedBallCollision(b, a);
				}
				else {
					HandleBallCollision(a, b);
				}
			}
		}
	}

}

void Physics::UpdateBallPosition(Ball& ball) {
	Vector2f deltaPosition = Vector2f(
		ball.getVelocity().getX() * DeltaTime,
		ball.getVelocity().getY() * DeltaTime
	);
	ball.setPosition(ball.getPosition() + deltaPosition);
}

void Physics::CheckBallWorldCollision(Ball& ball) {

	// Upper edge
	if (ball.getPosition().getY() > worldHeight / 2 - ball.getRadius()) {
		ball.getVelocity().reflect(Vector2f::Down());
	}

	// Right edge
	if (ball.getPosition().getX() > worldWidth / 2 - ball.getRadius()) {
		ball.getVelocity().reflect(Vector2f::Left());
	}

	// Bottom edge
	if (ball.getPosition().getY() < -(worldHeight / 2 - ball.getRadius())) {
		ball.getVelocity().reflect(Vector2f::Up());
	}

	// Left edge
	if (ball.getPosition().getX() < -(worldWidth / 2 - ball.getRadius())) {
		ball.getVelocity().reflect(Vector2f::Right());
	}
}

void Physics::CheckBallSolidity(vector<Ball>& balls) {
	for (int i = 0; i < balls.size(); i++) {
		Ball& a = balls[i];
		if (!a.isSolid()) {
			bool isColliding = false;
			for (int j = 0; j < balls.size(); j++) {

				// Don't check against itself.
				if (i == j) {
					continue;
				}

				Ball& b = balls[j];
				if (BallsCollided(a, b)) {
					isColliding = true;
					break;
				}
			}
			if (!isColliding) {
				a.setSolid(true);
			}
		}
	}
}

bool Physics::BallsCollided(Ball& a, Ball& b) {
	return Vector2f::Distance(a.getPosition(), b.getPosition()) <= a.getRadius() + b.getRadius();
}

void Physics::HandleLockedBallCollision(Ball & lockedBall, Ball & anotherBall) {

	// Modified version of the algorithm from https://csns.calstatela.edu/download?fileId=6114722

	// Find unit vecotr n from the point of collision for the first ball and the point of collision of the second ball.
	Vector2f n = (anotherBall.getPosition() - lockedBall.getPosition()).unitVector();

	// Calculate the K-value that takes into account the velocities of both balls.
	float K = 2 * (Vector2f::Dot(lockedBall.getVelocity(), n) - Vector2f::Dot(anotherBall.getVelocity(), n)) / (9999999 + anotherBall.getMass());

	// Calculate the new velocity of each ball using K-value.
	//a.setVelocity(lockedBall.getVelocity() - K * anotherBall.getMass() * n);
	anotherBall.setVelocity(anotherBall.getVelocity() + K * 9999999 * n);

}

void Physics::HandleBallCollision(Ball& a, Ball& b) {

	// Algorithm from https://csns.calstatela.edu/download?fileId=6114722
	// a = ball 1, b = ball 2

	// Find unit vecotr n from the point of collision for the first ball and the point of collision of the second ball.
	Vector2f n = (b.getPosition() - a.getPosition()).unitVector();

	// Calculate the K-value that takes into account the velocities of both balls.
	float K = 2 *(Vector2f::Dot(a.getVelocity(), n) - Vector2f::Dot(b.getVelocity(), n)) / (a.getMass() + b.getMass());

	// Calculate the new velocity of each ball using K-value.
	a.setVelocity(a.getVelocity() - K * b.getMass() * n);
	b.setVelocity(b.getVelocity() + K * a.getMass() * n);

}