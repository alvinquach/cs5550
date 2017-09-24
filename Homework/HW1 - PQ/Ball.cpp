// Alvin Quach, 300793745
// CS5550 F17 - HW1 PQ

#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include "Random.h"
#include "Ball.h"
#include "Random.h"

const int Ball::VertexCount = 32;
const float Ball::Density = 1.0;
const float Ball::DefaultRadius = 5.0;
const float Ball::MinRadius = 2.5;
const float Ball::MaxRadius = 7.5;
const float Ball::MaxMomentum = 10000.0;
const float Ball::MinInitialRadius = 3.7;
const float Ball::MaxInitialRadius = 6.9;
const float Ball::MinInitialMomentum = 2500.0;
const float Ball::MaxInitialMomentum = 5000.0;

int Ball::RandomBallCounter = 0;

vector<AvailableColor> Ball::AvailableColors = {
	{ ColorRGB(213, 0, 0), ColorRGB(255, 138, 128), 0 }, 
	{ ColorRGB(197, 17, 98), ColorRGB(255, 128, 171), 0 }, 
	{ ColorRGB(170, 0, 255), ColorRGB(234, 128, 252), 0 }, 
	{ ColorRGB(98, 0, 234), ColorRGB(179, 136, 255), 0 }, 
	{ ColorRGB(48, 79, 254), ColorRGB(140, 158, 255), 0 }, 
	{ ColorRGB(41, 98, 255), ColorRGB(130, 177, 255), 0 }, 
	{ ColorRGB(0, 145, 234), ColorRGB(128, 216, 255), 0 }, 
	{ ColorRGB(0, 184, 212), ColorRGB(132, 255, 255), 0 }, 
	{ ColorRGB(0, 191, 165), ColorRGB(167, 255, 235), 0 }, 
	{ ColorRGB(0, 200, 83), ColorRGB(185, 246, 202), 0 }, 
	{ ColorRGB(100, 221, 23), ColorRGB(204, 255, 144), 0 }, 
	{ ColorRGB(174, 234, 0), ColorRGB(244, 255, 129), 0 }, 
	{ ColorRGB(255, 214, 0), ColorRGB(255, 255, 141), 0 }, 
	{ ColorRGB(255, 171, 0), ColorRGB(255, 229, 127), 0 }, 
	{ ColorRGB(255, 109, 0), ColorRGB(255, 209, 128), 0 }, 
	{ ColorRGB(221, 44, 0), ColorRGB(255, 158, 128), 0 }
};

Ball Ball::Random() {
	Ball ball = Ball(Random::RandomFloat(MinInitialRadius, MaxInitialRadius));
	float mass = ball.getMass();
	float speed = Random::RandomFloat(MinInitialMomentum / mass, MaxInitialMomentum / mass);
	float direction = Random::RandomFloat(2 * M_PI);
	ball.setVelocity(Vector2f(speed * cos(direction), speed * sin(direction)));
	AvailableColor& randomColor = GetRandomColor();
	ball.setColor(randomColor.color);
	ball.setHighlight(randomColor.highlight);
	return ball;
}

AvailableColor& Ball::GetRandomColor() {
	int counter = RandomBallCounter / AvailableColors.size();
	vector<int> availableColorIndices;
	for (int i = 0; i < AvailableColors.size(); i++) {
		if (AvailableColors[i].counter == counter) {
			availableColorIndices.push_back(i);
		}
	}
	AvailableColor& result = AvailableColors[availableColorIndices[Random::RandomInt(availableColorIndices.size())]];
	result.counter++;
	RandomBallCounter++;
	return result;
}

Ball::Ball(): Ball(DefaultRadius) {}

Ball::Ball(float radius) {
	position = Vector2f::Zero();
	position = Vector2f::Zero();
	Ball::radius = radius;
	color = ColorRGB();
	highlight = ColorRGB();
	filled = true;
	solid = false;
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
	Ball::radius = radius < MinRadius ? MinRadius : radius > MaxRadius ? MaxRadius : radius;
}

void Ball::setRadius(float radius, bool preserveMomentum) {
	if (!preserveMomentum) {
		setRadius(radius);
		return;
	}
	float momentum = getMass() * velocity.getMagnitude();
	setRadius(radius);
	velocity.setMagnitude(momentum / getMass());
}

ColorRGB& Ball::getColor() {
	return color;
}

void Ball::setColor(ColorRGB& color) {
	Ball::color = color;
}

ColorRGB& Ball::getHighlight() {
	return highlight;
}

void Ball::setHighlight(ColorRGB& highlight) {
	Ball::highlight = highlight;
}

bool Ball::isFilled() {
	return filled;
}

void Ball::toggleFilled() {
	filled = !filled;
}

bool Ball::isSolid() {
	return solid;
}

void Ball::setSolid(bool solid) {
	Ball::solid = solid;
}

float Ball::getSpeed() {
	return velocity.getMagnitude();
}

void Ball::setSpeed(float speed) {
	float maxSpeed = MaxMomentum / getMass();
	velocity.setMagnitude(speed > maxSpeed ? maxSpeed : speed);
}

float Ball::getMass() {
	return 4 / 3 * M_PI * pow(radius, 3) * Density;
}

