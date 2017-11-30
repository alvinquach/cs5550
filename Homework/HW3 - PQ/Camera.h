#pragma once
#include "glut.h"
#include "Vector3f.h"

class Camera {

public:

	/// <summary>Field of view of the camera.</summary>
	static const float FieldOfView;

	/// <summary>Distance of the near-Z clipping plane from the camera.</summary>
	static const float NearZClipPlane;

	/// <summary>Distance of the far-Z clipping plane from the camera.</summary>
	static const float FarZClipPlane;

	static float GetLookDistance();

	static void LookAt(Vector3f& eye, Vector3f& look);

	static void LookAt();

	static void TransitionTo(Vector3f& look, int duration);

	static void TransitionTo(Vector3f& look, float lookDistance, int duration);

	static void TransitionTo(Vector3f& eye, Vector3f& look, int duration);

	static void PlayAnimation(Vector3f& target);

	/// <summary>Pivots the camera about its focus point, relative to the camera's local axes.</summary>
	static void Pivot(float pitch, float yaw);

	/// <summary>Translates the camera relative to the world axes. </summary>
	static void Translate(float x, float y, float z);

	/// <summary>
	///	Translates the camera relative to the camera's u and v axes.
	/// Movement amount is scaled by the look distance.
	/// </summary>
	static void LocalTranslate(float deltaU, float deltaV);

	/// <summary>
	/// Translates the camera relative to the camera n axis.
	/// Movement is capped if look distance becomes zero.
	/// </summary>
	static void Zoom(float amount);

	/// <summary>Interrupts the camera's animation.</summary>
	static void Interrupt();

	static void Update(float deltaTime);

	static float* GetModelViewMatrix();

	static Vector3f& GetWorldCoordinatesOf(float x, float y, float distance);

	static Vector3f7 RotateAboutE

	static float GetDistanceFrom(Vector3f& point);

private:
	static const int AnimationLookTransitionDuration;
	static int AnimationCounter;
	static Vector3f LookDelta, EyeDelta;
	static Vector3f Look, Eye, u, v, n;
	static float* ModelViewMatrix;
	static void SetModelViewMatrix();
};
