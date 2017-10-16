#include "Draw.h"

const float Draw::AxesLength = 100.0;

// TODO Assign actual values to this.
Vector3f& Draw::RoomDimensions = Vector3f();

void Draw::DrawAxes() {

	glBegin(GL_LINES);

	//x
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(AxesLength, 0, 0);
	//y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, AxesLength, 0);
	//z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, AxesLength);

	glEnd();

}

void Draw::DrawFloor() {

	// TODO Create separate variables for each property.
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(0, -0.2, 0);
	glScalef(1, 0.1, 1);
	glutSolidCube(2);
	glPopMatrix();

}


