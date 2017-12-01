// Alvin Quach, 300793745
// CS5550 F17 - HW3 PQ

#include <windows.h>
#include "glut.h"

#include "Utils.h"

#include "Mesh.h"

Mesh::Mesh() {
	scale = 1.0f;
	translation = Vector3f::Zero();
	rotation = Utils::Identity4x4();
}

Mesh::~Mesh() {

}

float Mesh::getScale() {
	return scale;
}

void Mesh::setScale(float scale) {
	Mesh::scale = scale;
}

Vector3f& Mesh::getTranslation() {
	return translation;
}

void Mesh::setTranslation(Vector3f& translation) {
	Mesh::translation = translation;
}

float* Mesh::getRotation() {
	return rotation;
}

void Mesh::setRotation(float* rotation) {
	Utils::CopyMatrix(rotation, Mesh::rotation, 16);
}

void Mesh::applyTransformations() {
	glTranslatef(translation.getX(), translation.getY(), translation.getZ());
	glScalef(scale, scale, scale);
	glMultMatrixf(rotation);
}

void Mesh::translate(Vector3f& delta) {
	translation = translation + delta;
}

void Mesh::rotate(float* rot) {
	float* newRotation = Utils::Multiply4x4x4x4(rot, rotation);
	rotation = newRotation;
}

void Mesh::resetTransformations() {
	scale = 1.0f;
	translation = Vector3f::Zero();
	Utils::SetIdentity4x4(rotation);
}