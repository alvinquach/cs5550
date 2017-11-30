#pragma once
#include "Vector3f.h"

class Mesh {

public:
	Mesh();
	~Mesh();
	float getScale();
	void setScale(float scale);
	Vector3f& getTranslation();
	void setTranslation(Vector3f& translation);
	Vector3f& getRotation();
	void setRotation(Vector3f& translation);
	void applyTransformations();
	void translate(Vector3f& delta);
	void rotate(Vector3f& delta);
	void resetTransformations();
private:
	float scale;
	Vector3f translation;
	Vector3f rotation;

};