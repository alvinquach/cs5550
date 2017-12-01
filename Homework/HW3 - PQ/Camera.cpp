#define _USE_MATH_DEFINES
#include <math.h>

#include "Utils.h"
#include "Window.h"

#include "camera.h"


#include <iostream>
using std::cout;
using std::endl;

const float Camera::FieldOfView = 45.0;
const float Camera::NearZClipPlane = 0.1;
const float Camera::FarZClipPlane = 100.0;

// Number of frames
const int Camera::AnimationLookTransitionDuration = 45;

// Initialize variables.
Vector3f Camera::Look = Vector3f::Zero();
Vector3f Camera::Eye = Vector3f::Zero();
Vector3f Camera::u = Vector3f::Zero();
Vector3f Camera::v = Vector3f::Zero();
Vector3f Camera::n = Vector3f::Zero();
float* Camera::ModelViewMatrix = Utils::Identity4x4();

int Camera::AnimationCounter = 0;
Vector3f Camera::LookDelta = Vector3f::Zero();
Vector3f Camera::EyeDelta = Vector3f::Zero();

float Camera::GetLookDistance() {
	return (Look - Eye).getMagnitude();
}

Vector3f& Camera::GetEyePosition() {
	return Eye;
}

void Camera::LookAt(Vector3f& eye, Vector3f& look) {
	Eye = eye;
	Look = look;
	LookAt();
}

void Camera::LookAt() {
	n = Eye - Look;
	u = Vector3f::Cross(Vector3f::Up(), n);
	n.normalize();
	u.normalize();
	v = Vector3f::Cross(n, u);
	SetModelViewMatrix();
}

void Camera::TransitionTo(Vector3f& look, int duration) {
	EyeDelta = LookDelta = (Look - look) / duration;
	AnimationCounter = duration;
}

void Camera::TransitionTo(Vector3f& look, float lookDistance, int duration) {
	LookDelta = (Look - look) / duration;
	EyeDelta = (Eye - look - lookDistance * n) / duration;
	AnimationCounter = duration;
}

void Camera::TransitionTo(Vector3f& eye, Vector3f& look, int duration) {
	LookDelta = (Look - look) / duration;
	EyeDelta = (Eye - eye) / duration;
	AnimationCounter = duration;
}

void Camera::PlayAnimation(Vector3f& target) {
	if (AnimationCounter < 0) {
		Interrupt();
	}
	else {
		LookDelta = (Look - target) / AnimationLookTransitionDuration;
		AnimationCounter = -AnimationLookTransitionDuration - 1;
	}
}

void Camera::Pivot(float pitch, float yaw) {

	// Apply the pitch rotation about camera's u-axis first.
	Vector3f nPitched = cos(pitch) * n + sin(pitch) * v;

	// Rotational matrix about the world's y-axis.
	float* rot = new float[16];
	rot[0] = cos(yaw);		rot[4] = 0.0f;		rot[8] = sin(yaw);		rot[12] = 0.0f;
	rot[1] = 0.0f;			rot[5] = 1.0f;		rot[9] = 0.0f;			rot[13] = 0.0f;
	rot[2] = -sin(yaw);		rot[6] = 0.0f;		rot[10] = cos(yaw);		rot[14] = 0.0f;
	rot[3] = 0.0f;			rot[7] = 0.0f;		rot[11] = 0.0f;			rot[15] = 1.0f;


	// Homogeneous coordinates of the n vector.
	float* homo = new float[4];
	homo[0] = nPitched.getX();
	homo[1] = nPitched.getY();
	homo[2] = nPitched.getZ();
	homo[3] = 0.0f;

	// Multiply the rotational matrix and the homogeneous matrix to get the rotated vector.
	float* nRotated = Utils::Multiply4x4x4x1(rot, homo);

	// Set new n.
	n = Vector3f(nRotated[0], nRotated[1], nRotated[2]);
	n.normalize();

	// Recalculate u and v for the camera.
	Camera::u = Vector3f::Cross(Vector3f::Up(), n);
	Camera::u.normalize();
	Camera::v = Vector3f::Cross(n, Camera::u);

	// If the look distance (distance between eye and look) is greater than zero, then recalculate the position of the camera.
	float lookDistance = (Eye - Look).getMagnitude();
	if (lookDistance > 0.0f) {
		Eye = lookDistance * n + Look;
	}

	// Delete arrays
	delete[] rot;
	delete[] homo;
	delete[] nRotated;
	
	SetModelViewMatrix();
}

void Camera::LocalTranslate(float deltaU, float deltaV) {

	// Calculate the translation vector.
	Vector3f delta = deltaU * u + deltaV * v;

	// Scale the vector by the look distance. This means that the closer the camera is to its "look at" point, the slower it will move.
	// If the camera is too close to the "look at" point, it will appear to be immovable. This behavior is also present in Blender.
	delta = (Eye - Look).getMagnitude() * delta;

	Eye = Eye - delta;
	Look = Look - delta;

	SetModelViewMatrix();
}

void Camera::Zoom(float amount) {
	float lookDistance = (Eye - Look).getMagnitude();
	if (lookDistance > 0 || amount < 0) {

		// Calculate the translation vector.
		Vector3f delta = amount * n;
		
		// Prevent the camera from moving past the look position, if needed.
		if (amount > lookDistance) {
			Eye = Look;
		}

		// Move camera normally;
		else {
			Eye = Eye - delta;
		}
	}

	SetModelViewMatrix();
}

void Camera::Interrupt() {
	AnimationCounter = 0;
	EyeDelta = Vector3f::Zero();
	LookDelta = Vector3f::Zero();
}

void Camera::Update(float deltaTime) {
	if (AnimationCounter < 0) {
		if (AnimationCounter < -1) {
			Look = Look - LookDelta;
			LookAt();
			AnimationCounter++;
		}
		Pivot(0.0f, deltaTime / 1000);
	}
	else if (AnimationCounter > 0) {
		Eye = Eye - EyeDelta;
		Look = Look - LookDelta;
		LookAt();
		AnimationCounter--;
	}
}

void Camera::SetModelViewMatrix() {
	glMatrixMode(GL_MODELVIEW);
	ModelViewMatrix[0] = u.getX();		ModelViewMatrix[4] = u.getY();		ModelViewMatrix[8] = u.getZ();		ModelViewMatrix[12] = -Vector3f::Dot(Eye, u);
	ModelViewMatrix[1] = v.getX();		ModelViewMatrix[5] = v.getY();		ModelViewMatrix[9] = v.getZ();		ModelViewMatrix[13] = -Vector3f::Dot(Eye, v);
	ModelViewMatrix[2] = n.getX();		ModelViewMatrix[6] = n.getY();		ModelViewMatrix[10] = n.getZ();		ModelViewMatrix[14] = -Vector3f::Dot(Eye, n);
	ModelViewMatrix[3] = 0.0f;			ModelViewMatrix[7] = 0.0f;			ModelViewMatrix[11] = 0.0f;			ModelViewMatrix[15] = 1.0f;
	glLoadMatrixf(ModelViewMatrix);
}

float* Camera::GetModelViewMatrix() {
	return ModelViewMatrix;
}

Vector3f Camera::GetWorldCoordinatesOf(float x, float y, float distance) {
	float aspect = Window::ScreenWidth / Window::ScreenHeight;
	float tanTheta = tan(M_PI / 180 * FieldOfView / 2);
	float thetaX = atan((2 * x / Window::ScreenWidth - 1) * aspect * tanTheta);
	float thetaY = atan((2 * (1 - y / Window::ScreenHeight) - 1) * tanTheta);
	return Eye + distance * (tan(thetaX) * u + tan(thetaY) * v - n);
}

float* Camera::GetRotationMatrixAboutLookDirection(float angle) {
	float x = n.getX();
	float y = n.getY();
	float z = n.getZ();
	float cosTheta = cos(angle);
	float sinTheta = sin(angle);
	float* result = new float[16];
	// See: https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
	result[0] = cosTheta + x * x * (1 - cosTheta);			result[4] = x * y * (1 - cosTheta) - z * sinTheta;		result[8] = x * z * (1 - cosTheta) + y * sinTheta;		result[12] = 0.0f;
	result[1] = y * x * (1 - cosTheta) + z * sinTheta;		result[5] = cosTheta + y * y * (1 - cosTheta);			result[9] = y * z * (1 - cosTheta) - x * sinTheta;		result[13] = 0.0f;
	result[2] = z * x * (1 - cosTheta) - y * sinTheta;		result[6] = z * y * (1 - cosTheta) + x * sinTheta;		result[10] = cosTheta + z * z * (1 - cosTheta);			result[14] = 0.0f;
	result[3] = 0.0f;										result[7] = 0.0f;										result[11] = 0.0f;										result[15] = 1.0f;
	return result;
}

float Camera::GetDistanceFrom(Vector3f& point) {
	return (Eye - point).getMagnitude();
}