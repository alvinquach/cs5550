// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#pragma once
#include "Vector3f.h"

struct CameraState {
	float angle;
	float distance;
	float verticalAngle;
	Vector3f target;
};

class Camera {

public:

	Camera();

	/// <summary>Calls the gluLookAt() function.</summary>
	void lookAt();

	/// <summary>Starts/stops the camera movement.</summary>
	void toggleAnimation();

	/// <summary>Zooms in.</summary>
	void zoomIn();

	/// <sumamry>Zooms Out.</summary>
	void zoomOut();

	/// <sumamry>Update animation.</summary>
	void updateAnimation(float t, Vector3f target);

private:

	static const float Height;
	static const float MaxDistance;
	static const float DefaultDistance;
	static const float MinDistance;
	static const float AngularVelocity;
	static const float ZoomSpeed;

	float angleLerp;
	float verticalAngleLerp;
	float distanceLerp;
	float targetLerp;

	float objectiveAngle;
	float objectiveDistance;
	float objectiveVerticalAngle;
	Vector3f objectiveTarget;

	float angleSpeed;
	float distanceSpeed;
	float verticalAngleSpeed;
	Vector3f targetSpeed;

	CameraState current;
	CameraState savedState;
	bool animationActive;
	float animationCooldown;

	void updateAngle();
	void updateVerticalAngle();
	void updateDistance();
	void updateTarget();

	void goToDistance(float distance);
	void goToAngle(float angle);
	void goToVerticalAngle(float verticalAngle);
	void goToTarget(Vector3f target);

	void saveState(CameraState& state);
	void applyState(CameraState& state);

};

