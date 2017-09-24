#include "Physics.h"
#include <windows.h>
#include <iostream>

const int Physics::UpdatesPerFrame = 10;

// This is calculated from UpdateRate.
const double Physics::DeltaTime = 1.0 / (UpdatesPerFrame * frameRate);

void Physics::UpdateBalls(vector<Ball>& balls) {

	// Update position based on velocity, and then check for collision with world.
	for (vector<Ball>::iterator ball = balls.begin(); ball != balls.end(); ++ball) {
		UpdateBallPosition(*ball);
		CheckBallWorldCollision(*ball);
	}

	// Check for collision against other balls.
	for (int i = 0; i < balls.size() - 1; i++) {
		Ball& a = balls[i];
		for (int j = i + 1; j < balls.size(); j++) {
			Ball& b = balls[j];
			if (BallsCollided(a, b)) {
				HandleBallCollision(a, b);
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

bool Physics::BallsCollided(Ball& a, Ball& b) {
	return Vector2f::Distance(a.getPosition(), b.getPosition()) <= a.getRadius() + b.getRadius();
}

void Physics::HandleBallCollision(Ball& a, Ball& b) {

	// Using the algorithm from https://csns.calstatela.edu/download?fileId=6114722
	// a = ball 1, b = ball 2

	// Find unit vecotr n from the point of collision for the first ball and the point of collision of the second ball.
	Vector2f n = (b.getPosition() - a.getPosition()).unitVector();

	// Calculate the K-value that takes into account the velocities of both balls.
	float K = 2 *(Vector2f::Dot(a.getVelocity(), n) - Vector2f::Dot(b.getVelocity(), n)) / (a.getMass() + b.getMass());

	// Calculate the new velocity of each ball using K-value.
	a.setVelocity(a.getVelocity() - K * b.getMass() * n);
	b.setVelocity(b.getVelocity() + K * a.getMass() * n);

}