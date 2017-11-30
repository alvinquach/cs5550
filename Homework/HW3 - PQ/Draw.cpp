// Alvin Quach, 300793745
// CS5550 F17 - HW3 PQ

#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>
#include "glut.h"

#include "Model.h"

#include "Draw.h"

/// <summary>Length of the rendered world axes.</summary>
float Draw::AxesLength = 100.0;

GLfloat Draw::GoldAmbient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
GLfloat Draw::GoldDiffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
GLfloat Draw::GoldSpecular[] = { 0.628281f, 0.555802f, 0.366065f, 1.0f };
GLfloat Draw::GoldShininess[] = { 0.4f * 128 };

// Cyan Plastic
GLfloat Draw::PlasticAmbient[] = { 0.0f, 0.1f, 0.06f, 1.0f };
GLfloat Draw::PlasticDiffuse[] = { 0.0f, 0.50980392f, 0.50980392f, 1.0f };
GLfloat Draw::PlasticSpecular[] = { 0.50196078f, 0.50196078f, 0.50196078f, 1.0f };
GLfloat Draw::PlasticShininess[] = { 0.25f * 128 };

int Draw::ActiveMaterial = 0;

void Draw::DrawAxes() {

	// Need to disable lighting to draw axes with color.
	glDisable(GL_LIGHTING);

	glBegin(GL_LINES);

	// x-axis
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(AxesLength, 0, 0);

	// y-axis
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, AxesLength, 0);

	// z-axis
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, AxesLength);

	glEnd();

	// Reenable lighting after drawing axes.
	glEnable(GL_LIGHTING);

}

void Draw::DrawTestObject() {
	SetMaterial();
	glPushMatrix();
	Model::GetMesh().applyTransformations();
	glutSolidTeapot(1.0);
	glPopMatrix();
}

void Draw::SetMaterial() {
	if (!ActiveMaterial) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, GoldAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, GoldDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, GoldSpecular);
		glMaterialfv(GL_FRONT, GL_SHININESS, GoldShininess);
	}
	else {
		glMaterialfv(GL_FRONT, GL_AMBIENT, PlasticAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, PlasticDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, PlasticSpecular);
		glMaterialfv(GL_FRONT, GL_SHININESS, PlasticShininess);
	}
}

void Draw::ToggleMaterial() {
	// Using the variable like a boolean since we only need 2 possible values anyways.
	ActiveMaterial = !ActiveMaterial;
}

