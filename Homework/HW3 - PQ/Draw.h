#pragma once
#include <vector>

#include "Spline.h"
#include "Vector3f.h"

using std::vector;

class Draw {

public:
	static void DrawAxes();
	static void DrawGrid(int mode);
	static void DrawSpline(Spline& spline);
	static void DrawTestObject();
	static void ToggleMaterial();

private:

	static GLfloat GoldAmbient[];
	static GLfloat GoldDiffuse[];
	static GLfloat GoldSpecular[];
	static GLfloat GoldShininess[];

	static GLfloat PlasticAmbient[];
	static GLfloat PlasticDiffuse[];
	static GLfloat PlasticSpecular[];
	static GLfloat PlasticShininess[];

	static float AxesLength;
	static float GridSpacing;
	static int ActiveMaterial;

	static void SetMaterial();
	static void DrawPoints(vector<Vector3f>& points, GLenum mode);
};