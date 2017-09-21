#include "Vector2f.h"
#include <math.h>

Vector2f::Vector2f() : Vector<float, 2>() {
	components[0] = 0;
	components[1] = 0;
}

Vector2f::Vector2f(float x, float y) : Vector<float, 2>() {
	components[0] = x;
	components[1] = y;
}

Vector2f Vector2f::up() {
	return Vector2f(0, 1);
}

Vector2f Vector2f::right() {
	return Vector2f(1, 0);
}

Vector2f Vector2f::down() {
	return Vector2f(0, -1);
}

Vector2f Vector2f::left() {
	return Vector2f(-1, 0);
}

Vector2f Vector2f::zero() {
	return Vector2f();
}

float Vector2f::getX() {
	return components[0];
}

void Vector2f::setX(float x) {
	components[0] = x;
}

float Vector2f::getY() {
	return components[1];
}

void Vector2f::setY(float y) {
	components[1] = y;
}

// Scalar multiplication operator overload
Vector2f operator *(float scalar, Vector2f vector) {
	return Vector2f(scalar * vector.getX(), scalar * vector.getY());
}