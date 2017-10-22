#define _USE_MATH_DEFINES
#include "Camera.h"
#include <math.h>
#include <Windows.h>
#include "glut.h"

/// <summary>Maximum distance the camera can be away from the target.</summary>
const float Camera::MaxDistance = 10.0;

/// <summary>The default distance that the camera is away from the target.</summary>
const float Camera::DefaultDistance = 6.9;

/// <summary>Minimum distance that camera can be from the target.</summary>
const float Camera::MinDistance = 1.0;

/// <summary>How fast the camera moves when in anaimation mode in rads/update.</summary>
const float Camera::AngularVelocity = M_PI / 360;

/// <summary>How fast the camera zooms.</summary>
const float Camera::ZoomSpeed = 1.2;

Camera::Camera() {
	objectiveAngle = M_PI / 4;
	objectiveVerticalAngle = M_PI / 4;
	objectiveDistance = DefaultDistance;
	objectiveTarget = Vector3f::Zero();
	current = {
		objectiveAngle,
		objectiveDistance,
		objectiveVerticalAngle,
		Vector3f::Zero()
	};
	saveState(current);
	angleSpeed = distanceSpeed = verticalAngleSpeed = targetSpeed = 0;
	angleLerp = 0.05;
	verticalAngleLerp = 0.05;
	distanceLerp = 0.05;
	targetLerp = 0.05;
	animationActive = false;
}

void Camera::lookAt() {
	gluLookAt(current.distance * cos(current.angle), current.distance * sin(current.verticalAngle), current.distance * sin(current.angle), 0, 0, 0, 0, 1, 0);
}

void Camera::toggleAnimation() {
	animationActive = !animationActive;
	if (animationActive) {
		distanceLerp = 0.02;
		angleLerp = 1.0;
		verticalAngleLerp = 0.02;
		saveState(current);
		applyState(CameraState {
			current.angle,
			2.0f,
			(float) M_PI / 12,
			Vector3f::Zero()
		});
	}
	else {
		distanceLerp = 0.05;
		angleLerp = 0.05;
		verticalAngleLerp = 0.05;
		applyState(savedState);
	}
}

void Camera::zoomIn() {
	if (animationActive) {
		return;
	}
	goToDistance(objectiveDistance / ZoomSpeed);
}

void Camera::zoomOut() {
	if (animationActive) {
		return;
	}
	goToDistance(objectiveDistance * ZoomSpeed);
}

void Camera::updateAnimation(float t, Vector3f target) {
	if (animationActive) {
		objectiveTarget = current.target = target;
		goToAngle(current.angle + AngularVelocity);
	}
	else {
		// Do something.
	}
	updateVerticalAngle();
	updateDistance();
	updateAngle();
	updateTarget(target);
}

void Camera::updateAngle() {
	if (current.angle < objectiveAngle) {
		current.angle += angleSpeed;
		if (objectiveAngle < current.angle) {
			current.angle = objectiveAngle;
			angleSpeed = 0;
		}
	}
	else if (current.angle > objectiveAngle) {
		current.angle -= angleSpeed;
		if (objectiveAngle > current.angle) {
			current.angle = objectiveAngle;
			angleSpeed = 0;
		}
	}
	if (current.angle == objectiveAngle) {
		// Wrap angle between 0 to 360 degrees.
		// This assumes that each update, the angle does not change more than 360 degrees.
		if (current.angle > 2 * M_PI) {
			current.angle -= 2 * M_PI;
		}
		else if (current.angle < 0) {
			current.angle += 2 * M_PI;;
		}
	}
}

void Camera::updateVerticalAngle() {
	if (current.verticalAngle < objectiveVerticalAngle) {
		current.verticalAngle += verticalAngleSpeed;
		if (objectiveVerticalAngle < current.verticalAngle) {
			current.verticalAngle = objectiveVerticalAngle;
			verticalAngleSpeed = 0;
		}
	}
	else if (current.verticalAngle > objectiveVerticalAngle) {
		current.verticalAngle -= verticalAngleSpeed;
		if (objectiveVerticalAngle > current.verticalAngle) {
			current.verticalAngle = objectiveVerticalAngle;
			verticalAngleSpeed = 0;
		}
	}
}

void Camera::updateDistance() {
	if (current.distance < objectiveDistance) {
		current.distance += distanceSpeed;
		if (objectiveDistance < current.distance) {
			current.distance = objectiveDistance;
			distanceSpeed = 0;
		}
	}
	else if (current.distance > objectiveDistance) {
		current.distance -= distanceSpeed;
		if (objectiveDistance > current.distance) {
			current.distance = objectiveDistance;
			distanceSpeed = 0;
		}
	}
}

void Camera::updateTarget(Vector3f target) {

}

void Camera::goToDistance(float distance) {
	if (distance > MaxDistance) {
		distance = MaxDistance;
	}
	else if (distance < MinDistance) {
		distance = MinDistance;
	}
	float newSpeed = abs(distance - current.distance) * distanceLerp;
	if (newSpeed > distanceSpeed) {
		distanceSpeed = newSpeed;
	}
	objectiveDistance = distance;
}

void Camera::goToAngle(float angle) {
	float newSpeed = abs(angle - current.angle) * angleLerp;
	if (newSpeed > angleSpeed) {
		angleSpeed = newSpeed;
	}
	objectiveAngle = angle;
}

void Camera::goToVerticalAngle(float verticalAngle) {
	float newSpeed = abs(verticalAngle - current.verticalAngle) * verticalAngleLerp;
	if (newSpeed > angleSpeed) {
		verticalAngleSpeed = newSpeed;
	}
	objectiveVerticalAngle = verticalAngle;
}

void Camera::saveState(CameraState& state) {
	savedState = {
		state.angle,
		state.distance,
		state.verticalAngle,
		state.target
	};
}

void Camera::applyState(CameraState& state) {
	goToDistance(state.distance);
	goToAngle(state.angle);
	goToVerticalAngle(state.verticalAngle);
}

