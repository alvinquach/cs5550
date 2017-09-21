#include "Physics.h"
#include <windows.h>
#include <iostream>

double Physics::DeltaTime = 1.0 / Physics::UpdateRate;

void Physics::UpdateBall(Ball& ball) {

	// Update position based on velocity.
	Vector2f deltaPosition = Vector2f(
		ball.getVelocity().getX() * DeltaTime,
		ball.getVelocity().getY() * DeltaTime
	);
	ball.setPosition(ball.getPosition() + deltaPosition);
	
	// Check for world collision

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


