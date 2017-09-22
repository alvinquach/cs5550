#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include "Random.h"
#include "Ball.h"
#include "Random.h"

const int Ball::VertexCount = 48;
const float Ball::Density = 1.0;
const float Ball::DefaultRadius = 5.0;
const float Ball::MinRadius = 1.0;
const float Ball::MaxRadius = 10.0;
const float Ball::MinInitialRadius = 3.7;
const float Ball::MaxInitialRadius = 6.9;
const float Ball::MinInitialMomentum = 2500;
const float Ball::MaxInitialMomentum = 5000;

int Ball::RandomBallCounter = 0;

vector<AvailableColor> Ball::AvailableColors = {
	{ ColorRGB(213, 0, 0), 0 },
	{ ColorRGB(197, 17, 98), 0 },
	{ ColorRGB(170, 0, 255), 0 },
	{ ColorRGB(98, 0, 234), 0 },
	{ ColorRGB(48, 79, 254), 0 },
	{ ColorRGB(41, 98, 255), 0 },
	{ ColorRGB(0, 145, 234), 0 },
	{ ColorRGB(0, 184, 212), 0 },
	{ ColorRGB(0, 191, 165), 0 },
	{ ColorRGB(0, 200, 83), 0 },
	{ ColorRGB(100, 221, 23), 0 },
	{ ColorRGB(174, 234, 0), 0 },
	{ ColorRGB(255, 214, 0), 0 },
	{ ColorRGB(255, 171, 0), 0 },
	{ ColorRGB(255, 109, 0), 0 },
	{ ColorRGB(221, 44, 0), 0 }
};

Ball Ball::Random() {
	Ball ball = Ball(Random::RandomFloat(MinInitialRadius, MaxInitialRadius));
	float mass = ball.getMass();
	float speed = Random::RandomFloat(MinInitialMomentum / mass, MaxInitialMomentum / mass);
	float direction = Random::RandomFloat(2 * M_PI);
	ball.setVelocity(Vector2f(speed * cos(direction), speed * sin(direction)));
	ball.setColor(GetRandomColor());
	return ball;
}

ColorRGB Ball::GetRandomColor() {
	int counter = RandomBallCounter / AvailableColors.size();
	vector<int> availableColorIndices;
	for (int i = 0; i < AvailableColors.size(); i++) {
		if (AvailableColors[i].counter == counter) {
			availableColorIndices.push_back(i);
		}
	}
	AvailableColor& color = AvailableColors[availableColorIndices[Random::RandomInt(availableColorIndices.size())]];
	color.counter++;
	RandomBallCounter++;
	return color.color;
}

Ball::Ball(): Ball(DefaultRadius) {}

Ball::Ball(float radius) {
	position = Vector2f::Zero();
	position = Vector2f::Zero();
	Ball::radius = radius;
}

Ball::~Ball() {

}

Vector2f& Ball::getPosition() {
	return position;
}

void Ball::setPosition(Vector2f& position) {
	Ball::position = position;
}

Vector2f& Ball::getVelocity() {
	return velocity;
}

void Ball::setVelocity(Vector2f& velocity) {
	Ball::velocity = velocity;
}

float Ball::getRadius() {
	return radius;
}

void Ball::setRadius(float radius) {
	Ball::radius = radius;
}

ColorRGB& Ball::getColor() {
	return color;
}

void Ball::setColor(ColorRGB& color) {
	Ball::color = color;
}

bool Ball::getLocked() {
	return locked;
}

float Ball::getMass() {
	return 4 / 3 * M_PI * pow(radius, 3) * Density;
}

