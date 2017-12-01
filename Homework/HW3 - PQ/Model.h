#pragma once
#include "Mesh.h"
#include "Spline.h"

class Model {
public:
	static void Reset();
	static Mesh& GetMesh();
	static Spline& GetSpline();
private:
	static Mesh& ModelMesh;
	static Spline& ModelSpline;
};