// Alvin Quach, 300793745
// CS5550 F17 - HW3 PQ

#pragma once
#include "Mesh.h"
#include "Spline.h"

class Model {
public:
	static int RevolutionSliceCount;
	static void Reset();
	static Mesh& GetMesh();
	static Spline& GetSpline();
	static void RevolveSpline(Spline& spline, int slices);
private:
	static Mesh& ModelMesh;
	static Spline& ModelSpline;
};