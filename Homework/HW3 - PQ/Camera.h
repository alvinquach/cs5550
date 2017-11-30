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

	static void LookAt(Vector3f& eye, Vector3f& look, Vector3f& up);

	static void LookAt(Vector3f& eye, Vector3f& look, Vector3f& up, float duration);

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

private:
	static Vector3f Look, Eye, u, v, n;
	static void Yaw(float angle);
	static void Pitch(float angle);
	static void Roll(float angle);
	static void SetModelViewMatrix();
};
