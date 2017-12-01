#include "Model.h"

Mesh& Model::ModelMesh = Mesh();
Spline& Model::ModelSpline = Spline();

void Model::Reset() {
	ModelMesh = Mesh();
	ModelSpline = Spline();
}

Mesh& Model::GetMesh() {
	return ModelMesh;
}

Spline& Model::GetSpline() {
	return ModelSpline;
}