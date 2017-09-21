#define _USE_MATH_DEFINES
#include <cmath>
#include "Random.h"
#include "Ball.h"

const int Ball::VertexCount = 48;
const float Ball::Density = 1.0;
const float Ball::DefaultRadius = 5.0;
const float Ball::MinRadius = 1.0;
const float Ball::MaxRadius = 10.0;
const float Ball::MinInitialRadius = 3.7;
const float Ball::MaxInitialRadius = 6.9;
const float Ball::MinInitialMomentum = 2000;
const float Ball::MaxInitialMomentum = 4000;

Ball Ball::Random() {
	Ball ball = Ball(Random::RandomFloat(MinInitialRadius, MaxInitialRadius));
	float mass = ball.getMass();
	float speed = Random::RandomFloat(MinInitialMomentum / mass, MaxInitialMomentum / mass);
	float direction = Random::RandomFloat(2 * M_PI);
	ball.setVelocity(Vector2f(speed * cos(direction), speed * sin(direction)));
	ball.setColor(ColorRGB::Random());
	return ball;
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

