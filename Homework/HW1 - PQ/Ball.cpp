#include "Ball.h"

Ball::Ball() {

}

Ball::~Ball() {

}

Vector2f Ball::getPosition() {
	return position;
}

void Ball::setPosition(Vector2f position) {
	Ball::position = position;
}

Vector2f Ball::getVelocity() {
	return velocity;
}

void Ball::setVelocity(Vector2f velocity) {
	Ball::velocity = velocity;
}

float Ball::getRadius() {
	return radius;
}

void Ball::setRadius(float radius) {
	Ball::radius = radius;
}

ColorRGB Ball::getColor() {
	return color;
}

void Ball::setColor(ColorRGB color) {
	Ball::color = color;
}
