#include <windows.h>
#include "glut.h"

#include "Mesh.h"

Mesh::Mesh() {
	scale = 1.0f;
	translation = Vector3f::Zero();
	rotation = Vector3f::Zero();
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

Vector3f& Mesh::getRotation() {
	return rotation;
}

void Mesh::setRotation(Vector3f& translation) {
	Mesh::rotation = rotation;
}

void Mesh::applyTransformations() {
	glTranslatef(translation.getX(), translation.getY(), translation.getZ());
	glScalef(scale, scale, scale);
	glRotatef(rotation.getY(), 0, 1, 0);
	glRotatef(rotation.getZ(), 0, 0, 1);
	glRotatef(rotation.getX(), 1, 0, 0);
}

void Mesh::translate(Vector3f& delta) {
	translation = translation + delta;
}

void Mesh::rotate(Vector3f& delta) {
	rotation = rotation + delta;
}

void Mesh::resetTransformations() {
	scale = 1.0f;
	translation = Vector3f::Zero();
	rotation = Vector3f::Zero();
}