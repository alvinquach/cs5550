// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#include "Vector3f.h"
#include <math.h>

Vector3f::Vector3f() : Vector<float, 3>() {
	components[0] = 0;
	components[1] = 0;
}

Vector3f::Vector3f(float x, float y) : Vector<float, 3>() {
	components[0] = x;
	components[1] = y;
}

Vector3f Vector3f::Up() {
	return Vector3f(0, 1);
}

Vector3f Vector3f::Right() {
	return Vector3f(1, 0);
}

Vector3f Vector3f::Down() {
	return Vector3f(0, -1);
}

Vector3f Vector3f::Left() {
	return Vector3f(-1, 0);
}

Vector3f Vector3f::Zero() {
	return Vector3f();
}

float Vector3f::getX() {
	return components[0];
}

void Vector3f::setX(float x) {
	components[0] = x;
}

float Vector3f::getY() {
	return components[1];
}

void Vector3f::setY(float y) {
	components[1] = y;
}

Vector3f Vector3f::unitVector() {
	float magnitude = getMagnitude();
	return Vector3f(components[0] / magnitude, components[1] / magnitude);
}

// Vector addition operator overload
Vector3f Vector3f::operator +(Vector3f anotherVector) {
	return Vector3f(components[0] + anotherVector[0], components[1] + anotherVector[1]);
}

// Vector subtraction operator overload
Vector3f Vector3f::operator -(Vector3f anotherVector) {
	return Vector3f(components[0] - anotherVector[0], components[1] - anotherVector[1]);
}

// Scalar division operator overload
Vector3f Vector3f::operator /(float scalar) {
	return Vector3f(components[0] / scalar, components[1] / scalar);
}

// Scalar multiplication operator overload
Vector3f operator *(float scalar, Vector3f vector) {
	return Vector3f(scalar * vector.getX(), scalar * vector.getY());
}