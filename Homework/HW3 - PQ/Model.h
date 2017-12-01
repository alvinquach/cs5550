#pragma once
#include "Mesh.h"
#include "Spline.h"

class Model {
public:
	static void Reset();
	static Mesh& GetMesh();
	static Spline& GetSpline();
	static void RevolveSpline(Spline& spline, int count);
private:
	static Mesh& ModelMesh;
	static Spline& ModelSpline;
};