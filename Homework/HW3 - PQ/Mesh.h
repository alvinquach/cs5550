#pragma once
#include <vector>

#include "Vector3f.h"

using std::vector;

struct Vertex {
	int vertexIndex;
	int normalIndex;
};

struct Face {
	vector<Vertex> vertices;
};

class Mesh {

public:
	Mesh();
	~Mesh();
	float getScale();
	void setScale(float scale);
	Vector3f& getTranslation();
	void setTranslation(Vector3f& translation);
	float* getRotation();
	void setRotation(float* translation);
	void applyTransformations();
	void translate(Vector3f& delta);
	void rotate(float* rot);
	void resetTransformations();

	// TODO Make these private
	vector<Vector3f> vertices;
	vector<Vector3f> normals;
	vector<Face> faces;
private:
	float scale;
	Vector3f translation;
	float* rotation;
};