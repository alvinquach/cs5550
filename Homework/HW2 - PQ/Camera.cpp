#define _USE_MATH_DEFINES
#include "Camera.h"
#include <math.h>
#include <Windows.h>
#include "glut.h"

/// <summary>Height of the camera.</summary>
const float Camera::Height = 0.69;

/// <summary>Maximum distance the camera can be away from the target.</summary>
const float Camera::MaxDistance = 13.37;

/// <summary>The default distance that the camera is away from the target.</summary>
const float Camera::DefaultDistance = 6.9;

/// <summary>Minimum distance that camera can be from the target.</summary>
const float Camera::MinDistance = 3.1;

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
	angleSpeed = distanceSpeed = verticalAngleSpeed = 0;
	//targetSpeed = Vector3f::Zero();
	angleLerp = 0.05;
	verticalAngleLerp = 0.05;
	distanceLerp = 0.05;
	targetLerp = 0.05;
	animationActive = false;
}

void Camera::lookAt() {
	gluLookAt(
		current.distance * cos(current.angle) + current.target.getX(),
		current.distance * sin(current.verticalAngle) + current.target.getY() + Height,
		current.distance * sin(current.angle) + current.target.getZ(),
		current.target.getX(),
		current.target.getY() + Height,
		current.target.getZ(),
		0, 1, 0
	);
}

void Camera::toggleAnimation() {
	if (animationCooldown > 0) {
		return;
	}
	animationActive = !animationActive;
	if (animationActive) {
		distanceLerp = 0.02;
		angleLerp = 1.0;
		verticalAngleLerp = 0.02;
		saveState(current);
		applyState(CameraState {
			current.angle,
			5.0f,
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
	animationCooldown = 1.0;
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
		animationCooldown = max(animationCooldown - 0.02, 0.0f);
		goToAngle(current.angle + AngularVelocity);
		goToTarget(target);
	}
	else {
		animationCooldown = max(animationCooldown - 0.05, 0.0f);
		goToTarget(0.69 * target);
	}
	updateVerticalAngle();
	updateDistance();
	updateAngle();
	updateTarget();
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

void Camera::updateTarget() {
	current.target = current.target + targetSpeed;
	if (Vector3f::Distance(current.target, objectiveTarget) < targetSpeed.getMagnitude()) {
		targetSpeed = Vector3f::Zero();
		current.target = objectiveTarget;
	}
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
	if (newSpeed > verticalAngleSpeed) {
		verticalAngleSpeed = newSpeed;
	}
	objectiveVerticalAngle = verticalAngle;
}

void Camera::goToTarget(Vector3f target) {
	targetSpeed = targetLerp * (target - current.target);
	objectiveTarget = target;
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

