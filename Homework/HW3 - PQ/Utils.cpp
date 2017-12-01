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

float Utils::Clamp(float value, float min, float max) {
	return value < min ? min : value > max ? max : value;
}

void Utils::CopyMatrix(float* from, float* to, int size) {
	for (int i = 0; i < size; i++) {
		to[i] = from[i];
	}
}

float* Utils::Identity4x4() {
	float* result = new float[16];
	for (int i = 0; i < 16; i++) {
		if (i % 5 == 0) {
			result[i] = 1.0f;
		}
		else {
			result[i] = 0.0f;
		}
	}
	return result;
}

void Utils::SetIdentity4x4(float* matrix) {
	for (int i = 0; i < 16; i++) {
		if (i % 5 == 0) {
			matrix[i] = 1.0f;
		}
		else {
			matrix[i] = 0.0f;
		}
	}
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

void Utils::PrintVector3f(Vector3f & vector) {
	cout << "(" << vector.getX() << ", " << vector.getY() << ", " << vector.getZ() << ")" << endl;
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

	float* multiplied = Multiply4x4x4x1(projection, camCoordinates);

	Vector2f& result = Vector2f(
		(1 + multiplied[0] / multiplied[3]) * Window::ScreenWidth / 2,
		(1 - multiplied[1] / multiplied[3]) * Window::ScreenHeight / 2  // Y-value is inverted to match mouse coordinates.
	);

	// Delete arrays
	delete[] homo;
	delete[] camCoordinates;
	delete[] multiplied;

	return result;
}

void Utils::AddPointToSpline(Vector3f& start, Vector3f& end, Spline& spline) {
	cout << "AddPointToSpline: ";
	Vector3f& n = Vector3f::Forward();
	Vector3f& c = end - start;
	c.normalize();
	float nc = Vector3f::Dot(n, c);
	if (!(nc > 0.0f || nc < 0.0f)) {
		cout << "n dot c is 0" << endl;
		return;
	}
	float tHit = Vector3f::Dot(n, -1 * start) / nc;
	Vector3f& pHit = start + tHit * c;
	cout << endl << "  distance: " << Vector3f::Distance(pHit, start) << endl;
	if (Vector3f::Distance(pHit, start) > Vector3f::Distance(end, start)) {
		return;
	}
	cout << "  ";
	PrintVector3f(pHit);
	cout << endl;
	spline.getPoints().push_back(pHit);
}