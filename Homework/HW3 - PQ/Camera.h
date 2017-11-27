#pragma once
#include "glut.h"
#include "Vector3f.h"

class Camera {

public:
	Camera();

	/// <summary> Pivots the camera about its focus point, relative to the camera's local axes. </summary>
	void pivot(float u, float v);

	/// <summary> Translates the camera relative to the world axes. </summary>
	void translate(float x, float y, float z);

	/// <summary> Translates the camera relative to the camera's local axes. </summary>
	void localTranslate(float u, float v);

private:
	float focusDistance;
	Vector3f position;
	Vector3f u, v, n;

};
