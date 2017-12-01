#define _USE_MATH_DEFINES
#include <math.h>

#include "Utils.h"

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

void Model::RevolveSpline(Spline& spline, int count) {

	vector<Vector3f>& points = spline.getPoints();
	int pointCount = (int)points.size();

	for (int i = 0; i <= count; i++) {

		float theta = 2 * M_PI / count * i;
		float cosTheta = cos(theta);
		float sinTheta = sin(theta);

		float* rot = new float[16];
		rot[0] = cosTheta;		rot[4] = 0.0f;		rot[8] = sinTheta;		rot[12] = 0.0f;
		rot[1] = 0.0f;			rot[5] = 1.0f;		rot[9] = 0.0f;			rot[13] = 0.0f;
		rot[2] = -sinTheta;		rot[6] = 0.0f;		rot[10] = cosTheta;		rot[14] = 0.0f;
		rot[3] = 0.0f;			rot[7] = 0.0f;		rot[11] = 0.0f;			rot[15] = 1.0f;

		for (int j = 0; j < pointCount; j++) {
			Vector3f& point = points[j];
			if (i == 0) {
				ModelMesh.vertices.push_back(point);
			}
			else {
				if (i < count) {

					// Rotate and insert vertices into list.
					float* homo = new float[4];
					homo[0] = point.getX();
					homo[1] = point.getY();
					homo[2] = point.getZ();
					homo[3] = 1.0f;
					float* rotated = Utils::Multiply4x4x4x1(rot, homo);
					ModelMesh.vertices.push_back(Vector3f(rotated[0], rotated[1], rotated[2]));

					// Delete arrays.
					delete[] homo;
					delete[] rotated;
				}

				// Set face vertices and normals
				if (j > 0) {
					int vert1 = j - 1 + (i == count ? 0 : i) * pointCount;
					int vert2 = j - 1 + (i - 1) * pointCount;
					int vert3 = j + (i - 1) * pointCount;
					int vert4 = j + (i == count ? 0 : i) * pointCount;
					Face face = Face();
					face.vertices.push_back({ vert1, 0 });
					face.vertices.push_back({ vert2, 0 });
					face.vertices.push_back({ vert3, 0 });
					face.vertices.push_back({ vert4, 0 });
					ModelMesh.faces.push_back(face);
				}
			}
		}
		delete[] rot;
	}
}