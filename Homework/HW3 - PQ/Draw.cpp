// Alvin Quach, 300793745
// CS5550 F17 - HW3 PQ

#define _USE_MATH_DEFINES
#include <math.h>
#include "glut.h"
#include "Draw.h"

/// <summary>Length of the rendered world axes.</summary>
float Draw::AxesLength = 100.0;

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