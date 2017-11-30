#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "Camera.h"
#include "Window.h"

#include "Utils.h"

using std::cout;
using std::endl;

float* Utils::test() {
	float * m = new float[4];
	for (int i = 0; i < 4; i++) {
		m[i] = 2 * i;
	}
	return m;
}

float* Utils::Multiply4x4x4x1(float* a, float* b) {
	float* result = new float[4];
	for (int i = 0; i < 4; i++) {
		float sum = 0;
		for (int j = 0; j < 4; j++) {
			sum += a[i + j * 4] * b[j];
		}
		result[i] = sum;
	}
	return result;
}

float* Utils::Multiply4x4x4x4(float* a, float* b) {
	float* result = new float[16];
	for (int i = 0; i < 16; i++) {
		float sum = 0;
		for (int j = 0; j < 4; j++) {
			sum += a[i % 4 + j * 4] * b[i / 4 * 4 + j];
		}
		result[i] = sum;
	}
	return result;
}

void Utils::Print4x4(float* matrix) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << matrix[i * 4 + j] << "\t";
		}
		cout << endl;
	}
}

void Utils::Print4x1(float* matrix) {
	for (int i = 0; i < 4; i++) {
		cout << matrix[i] << "\t";
	}
	cout << endl;
}

float Utils::Clamp(float value, float min, float max) {
	return value < min ? min : value > max ? max : value;
}

Vector2f& Utils::GetScreenCoordnates(Vector3f& point) {
	float* homo = new float[4];
	homo[0] = point.getX();
	homo[1] = point.getY();
	homo[2] = point.getZ();
	homo[3] = 1.0f;

	float* camCoordinates = Multiply4x4x4x1(Camera::GetModelViewMatrix(), homo);

	GLfloat projection[16];
	glGetFloatv(GL_PROJECTION_MATRIX, projection);

	float* result = Multiply4x4x4x1(projection, camCoordinates);

	return Vector2f(
		(result[0] / result[3] + 1) * Window::ScreenWidth / 2,
		(result[1] / result[3] + 1) * Window::ScreenHeight / 2
	);
}