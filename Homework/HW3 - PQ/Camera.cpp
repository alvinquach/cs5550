#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "Utils.h"

#include "camera.h"

const float Camera::FieldOfView = 30.0;
const float Camera::NearZClipPlane = 0.1;
const float Camera::FarZClipPlane = 100.0;

// Initialize variables.
Vector3f Camera::Look = Vector3f::Zero();
Vector3f Camera::Eye = Vector3f::Zero();
Vector3f Camera::u = Vector3f::Zero();
Vector3f Camera::v = Vector3f::Zero();
Vector3f Camera::n = Vector3f::Zero();

void Camera::LookAt(Vector3f& eye, Vector3f& look, Vector3f& up) {
	Eye = eye;
	Look = look;
	n = eye - look;
	u = Vector3f::Cross(up, n);
	n.normalize();
	u.normalize();
	v = Vector3f::Cross(n, u);
	SetModelViewMatrix();
}

void Camera::LookAt(Vector3f& eye, Vector3f& look, Vector3f& up, float duration) {
	LookAt(eye, look, up);
	// TODO Implement duration
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
	float gay = v.getMagnitude();

	// If the look distance (distance between eye and look) is greater than zero, then recalculate the position of the camera.
	float lookDistance = (Eye - Look).getMagnitude();
	if (lookDistance > 0.0f) {
		Eye = lookDistance * n + Look;
	}
	
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
	//SetModelViewMatrix();
}

void Camera::Update(float deltaTime) {
	//SetModelViewMatrix();
}

void Camera::SetModelViewMatrix() {
	float m[16];
	m[0] = u.getX();	m[4] = u.getY();	m[8] = u.getZ();	m[12] = -Vector3f::Dot(Eye, u);
	m[1] = v.getX();	m[5] = v.getY();	m[9] = v.getZ();	m[13] = -Vector3f::Dot(Eye, v);
	m[2] = n.getX();	m[6] = n.getY();	m[10] = n.getZ();	m[14] = -Vector3f::Dot(Eye, n);
	m[3] = 0.0f;		m[7] = 0.0f;		m[11] = 0.0f;		m[15] = 1.0f;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
}