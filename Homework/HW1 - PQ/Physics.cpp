// Alvin Quach, 300793745
// CS5550 F17 - HW1 PQ

#include "Physics.h"
#include "Scene.h"
#include <windows.h>

const int Physics::UpdatesPerFrame = 10;

// This is calculated from UpdateRate.
const double Physics::DeltaTime = 1.0 / (UpdatesPerFrame * frameRate);

Vector2f Physics::LockedBallLastPosition = Vector2f::Zero();

void Physics::UpdateBalls() {

	// Get balls from scene.
	vector<Ball>& balls = Scene::GetInstance().GetBalls();

	// Update position based on velocity, and then check for collision with world.
	for (int i = 0; i < balls.size(); i++) {
		Ball& ball = balls[i];
		if (i == Scene::GetLockedBallIndex()) {
			UpdateLockedBallVelocity(ball);
		}
		else {
			UpdateBallPosition(ball);
			CheckBallWorldCollision(ball);
		}
	}

	// Check and update solidity status of balls.
	CheckBallSolidity(balls);

	// Check for collision against other balls.
	for (int i = 0; i < balls.size() - 1; i++) {
		Ball& a = balls[i];

		// Skip the ball if it's not solid.
		if (!a.isSolid()) {
			continue;
		}

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

void Physics::SampleLockedBallPosition() {
	Ball *lockedBall = Scene::GetLockedBall();
	if (lockedBall) {
		LockedBallLastPosition = lockedBall->getPosition();
	}
}

void Physics::MoveLockedBall(Vector2f& newPosition) {

	Ball *lockedBall = Scene::GetLockedBall();
	
	if (lockedBall) {
		
		float radius = lockedBall->getRadius();

		// Check for collision with world.
		// Upper edge
		if (newPosition.getY() >= worldHeight / 2 - radius) {
			newPosition.setY(worldHeight / 2 - radius);
		}

		// Right edge
		if (newPosition.getX() >= worldWidth / 2 - radius) {
			newPosition.setX(worldWidth / 2 - radius);
		}

		// Bottom edge
		if (newPosition.getY() <= radius - worldHeight / 2) {
			newPosition.setY(radius - worldHeight / 2);
		}

		// Left edge
		if (newPosition.getX() <= radius - worldWidth / 2) {
			newPosition.setX(radius - worldWidth / 2);
		}

		// Set new position of the locked ball.
		lockedBall->setPosition(newPosition);
	}
}

void Physics::UpdateBallPosition(Ball& ball) {
	ball.setPosition(ball.getPosition() + DeltaTime * ball.getVelocity());
}

void Physics::UpdateLockedBallVelocity(Ball & ball) {
	ball.setVelocity(frameRate * (ball.getPosition() - LockedBallLastPosition));
}

void Physics::CheckBallWorldCollision(Ball& ball) {

	float radius = ball.getRadius();

	// Upper edge
	if (ball.getPosition().getY() >= worldHeight / 2 - radius) {
		ball.getPosition().setY(worldHeight / 2 - radius);
		ball.getVelocity().reflect(Vector2f::Down());
	}

	// Right edge
	if (ball.getPosition().getX() >= worldWidth / 2 - radius) {
		ball.getPosition().setX(worldWidth / 2 - radius);
		ball.getVelocity().reflect(Vector2f::Left());
	}

	// Bottom edge
	if (ball.getPosition().getY() <= radius - worldHeight / 2) {
		ball.getPosition().setY(radius - worldHeight / 2);
		ball.getVelocity().reflect(Vector2f::Up());
	}

	// Left edge
	if (ball.getPosition().getX() <= radius - worldWidth / 2) {
		ball.getPosition().setX(radius - worldWidth / 2);
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

void Physics::HandleLockedBallCollision(Ball & lockedBall, Ball & unlockedBall) {

	// Modified version of the algorithm from https://csns.calstatela.edu/download?fileId=6114722

	// Calculate the distance D = |c1c2| between the two points of collision where c1 and c2 are center locations of two balls.
	float D = Vector2f::Distance(lockedBall.getPosition(), unlockedBall.getPosition());

	// Find unit vecotr n from the point of collision for the first ball and the point of collision of the second ball.
	Vector2f n = (unlockedBall.getPosition() - lockedBall.getPosition()) / D;

	// Calculate the K-value and multiply by M1, then take the limit as M1 approaches infinity, 
	// since a ball that is locked to mouse movement is treated as having infinite mass.
	// The resulting K*M1 = 2 * (A1 + A2) as M1 -> infinity.
	float K_M1 = 2 * (Vector2f::Dot(lockedBall.getVelocity(), n) - Vector2f::Dot(unlockedBall.getVelocity(), n));

	// Calculate the new velocity of each ball using K-value.
	unlockedBall.setVelocity(unlockedBall.getVelocity() + K_M1 * n);

	// Also move the unlocked ball so that it does not intersect with the locked ball.
	if (D < lockedBall.getRadius() + unlockedBall.getRadius()) {
		unlockedBall.setPosition(unlockedBall.getPosition() + (lockedBall.getRadius() + unlockedBall.getRadius() - D) * n);
	}

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