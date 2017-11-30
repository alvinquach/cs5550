#include "Model.h"

Mesh& Model::ModelMesh = Mesh();

void Model::Reset() {
	ModelMesh = Mesh();
}

Mesh& Model::GetMesh() {
	return ModelMesh;
}