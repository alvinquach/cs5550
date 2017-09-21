#define _USE_MATH_DEFINES
#include <cmath>
#include "Ball.h"

const int Ball::VertexCount = 48;
const float Ball::Density = 1.0;

Ball::Ball() {
	position = Vector2f::Zero();
	position = Vector2f::Zero();
	radius = 10;
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

float Ball::getMass() {
	return 4 / 3 * M_PI * pow(radius, 3) * Density;
}

