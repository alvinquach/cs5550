#pragma once
#include "Spline.h"
#include "Vector2f.h"
#include "Vector3f.h"

class Utils {
public:
	static float Clamp(float value, float min, float max);
	static void CopyMatrix(float* from, float* to, int size);
	static float* Identity4x4();
	static void SetIdentity4x4(float* matrix);
	static float* Multiply4x4x4x1(float* a, float* b);
	static float* Multiply4x4x4x4(float* a, float* b);
	static void Print4x4(float* matrix);
	static void Print4x1(float* matrix);
	static void PrintVector3f(Vector3f& vector);
	static Vector2f& GetScreenCoordnates(Vector3f& point);
	static void AddPointToSpline(Vector3f& start, Vector3f& end, Spline& spline);
	static Vector3f& NewellsMethod(Vector3f* vertices);
	static float* test();
};