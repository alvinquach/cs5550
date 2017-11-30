#pragma once
#include "Mesh.h"

class Model {
public:
	static void Reset();
	static Mesh& GetMesh();
private:
	static Mesh& ModelMesh;
};