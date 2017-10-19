// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#include "Vector3f.h"
#include <math.h>

Vector3f::Vector3f() : Vector<float, 3>() {
	components[0] = 0;
	components[1] = 0;
	components[2] = 0;
}

Vector3f::Vector3f(float x, float y, float z) : Vector<float, 3>() {
	components[0] = x;
	components[1] = y;
	components[2] = z;
}

Vector3f Vector3f::Up() {
	return Vector3f(0, 1, 0);
}

Vector3f Vector3f::Right() {
	return Vector3f(1, 0, 0);
}

Vector3f Vector3f::Down() {
	return Vector3f(0, -1, 0);
}

Vector3f Vector3f::Left() {
	return Vector3f(-1, 0, 0);
}

Vector3f Vector3f::Forward() {
	return Vector3f(0, 0, 1);
}

Vector3f Vector3f::Back() {
	return Vector3f(0, 0, -1);
}

Vector3f Vector3f::Zero() {
	return Vector3f();
}

Vector3f Vector3f::Cross(Vector3f a, Vector3f b) {
	return Vector3f(
		a[1] * b[2] - a[2] * b[1],
		a[2] * b[0] - a[0] * b[2],
		a[0] * b[1] - a[1] * b[0]
	);
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

float Vector3f::getZ() {
	return components[2];
}

void Vector3f::setZ(float z) {
	components[2] = z;
}

Vector3f Vector3f::unitVector() {
	float magnitude = getMagnitude();
	return Vector3f(components[0] / magnitude, components[1] / magnitude, components[2] / magnitude);
}

// Vector addition operator overload
Vector3f Vector3f::operator +(Vector3f anotherVector) {
	return Vector3f(components[0] + anotherVector[0], components[1] + anotherVector[1], components[2] + anotherVector[2]);
}

// Vector subtraction operator overload
Vector3f Vector3f::operator -(Vector3f anotherVector) {
	return Vector3f(components[0] - anotherVector[0], components[1] - anotherVector[1], components[2] - anotherVector[2]);
}

// Scalar division operator overload
Vector3f Vector3f::operator /(float scalar) {
	return Vector3f(components[0] / scalar, components[1] / scalar, components[2] / scalar);
}

// Scalar multiplication operator overload
Vector3f operator *(float scalar, Vector3f vector) {
	return Vector3f(scalar * vector.getX(), scalar * vector.getY(), scalar * vector.getZ());
}