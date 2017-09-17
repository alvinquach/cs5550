#include "Vector2f.h"
#include <math.h>

Vector2f::Vector2f() : Point2f() {}

Vector2f::Vector2f(float x, float y) : Point2f(x, y) {}

float Vector2f::Vector2f::getMagnitude() {
	return sqrt(pow(x, 2) + pow(y, 2));
}

void Vector2f::setMagnitude(float magnitude) {
	float scale = magnitude / Vector2f::getMagnitude();
	x *= scale;
	y *= scale;
}

void Vector2f::normalize() {
	setMagnitude(1.0);
}

Vector2f operator *(float scalar, Vector2f vector) {
	return Vector2f(scalar * vector.getX(), scalar * vector.getY());
}