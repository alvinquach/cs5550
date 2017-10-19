#include "Draw.h"
#include "Scene.h"

const float Draw::AxesLength = 100.0;

const float Draw::RoomFloorThickness = 0.1;

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
	glTranslatef(0, -Draw::RoomFloorThickness / 2, 0);
	glScalef(Scene::GetRoomDimensions().getX(), Draw::RoomFloorThickness, Scene::GetRoomDimensions().getZ());
	glutSolidCube(1);
	glPopMatrix();

}


