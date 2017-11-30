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
	float* getRotation();
	void setRotation(float* translation);
	void applyTransformations();
	void translate(Vector3f& delta);
	void rotate(float* rot);
	void resetTransformations();
private:
	float scale;
	Vector3f translation;
	float* rotation;

};