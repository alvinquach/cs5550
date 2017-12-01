// Alvin Quach, 300793745
// CS5550 F17 - HW1 PQ

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

Vector2f Vector2f::Up() {
	return Vector2f(0, 1);
}

Vector2f Vector2f::Right() {
	return Vector2f(1, 0);
}

Vector2f Vector2f::Down() {
	return Vector2f(0, -1);
}

Vector2f Vector2f::Left() {
	return Vector2f(-1, 0);
}

Vector2f Vector2f::Zero() {
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

float Vector2f::angle() {
	return atan2(components[1], components[0]);
}

Vector2f Vector2f::unitVector() {
	float magnitude = getMagnitude();
	return Vector2f(components[0] / magnitude, components[1] / magnitude);
}

// Vector addition operator overload
Vector2f Vector2f::operator +(Vector2f anotherVector) {
	return Vector2f(components[0] + anotherVector[0], components[1] + anotherVector[1]);
}

// Vector subtraction operator overload
Vector2f Vector2f::operator -(Vector2f anotherVector) {
	return Vector2f(components[0] - anotherVector[0], components[1] - anotherVector[1]);
}

// Scalar division operator overload
Vector2f Vector2f::operator /(float scalar) {
	return Vector2f(components[0] / scalar, components[1] / scalar);
}

// Scalar multiplication operator overload
Vector2f operator *(float scalar, Vector2f vector) {
	return Vector2f(scalar * vector.getX(), scalar * vector.getY());
}