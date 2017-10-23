#include "Ball.h"

const float Ball::Mass = 10;
const float Ball:: Radius = 0.125;
ColorRGB Ball::Color = ColorRGB(3, 169, 244);

Ball::Ball() {
	position = Vector3f::Zero();
	velocity = Vector3f::Zero();
}

Ball::~Ball() {

}

Vector3f& Ball::getPosition() {
	return position;
}

void Ball::setPosition(Vector3f& position) {
	Ball::position = position;
}

Vector3f& Ball::getVelocity() {
	return velocity;
}

void Ball::setVelocity(Vector3f& velocity) {
	Ball::velocity = velocity;
}