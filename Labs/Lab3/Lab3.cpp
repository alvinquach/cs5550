//Computer Graphics Lab - Animation
#include <windows.h>
#include <iostream>
#include <cmath>
#include <gl/Gl.h>
#include "glut.h"

#include "Lab3.h"

using namespace std;

/// <summary>Function to calculate coordinates of triangle.</summary>
/// <param name='n'>The nth corner of the corresponding hexagon (ie. n = 0 and n = 1 are both the first corner of the triangle).</param>
/// <returns>The coordinates of the triangle point.</returns>
GLfloatPoint2D generateTrianglePoint(int n) {

	// Calculate the radius of the triangle such that it equals the inradius of the hexagon.
	float triangleRadius = hexagonRadius * sqrt(3) / 2;

	// Calculate theta such that the first corner (n = 0) is at 90 degs.
	// We need to divide n by 2 because one point on the triangle represents two ponts on the hexagon.
	float theta = (n / 2) * PI / 1.5 + PI / 2;

	// Return the calculated point
	return { triangleRadius * cos(theta), triangleRadius * sin(theta) };
}

/// <summary>Function to calculate coordinates of hexagon.</summary>
/// <param name='n'>The nth corner of the hexagon.</param>
/// <returns>The coordinates of the hexagon point.</returns>
GLfloatPoint2D generateHexagonPoint(int n) {

	// Calculate theta such that the first corner (n = 0) is at 90 degs.
	float theta = n * PI / 3 + PI / 3;

	// Return the calculated point
	return { hexagonRadius * cos(theta), hexagonRadius * sin(theta) };
}

void myInit(void)
 {
    glClearColor(1.0,1.0,1.0,0.0);      // background color is white
    glColor3f(0.0f, 0.0f, 1.0f);        // drawing color is blue

 	setWindow(-worldWidth/2, worldWidth/2, -worldHeight/2, worldHeight/2); // set the world window

	// Set radius of hexagon to be 0.25 of the world dimensions.
	hexagonRadius = min(worldWidth, worldHeight) / 4;

	// Init points to form a triangle
	for (int i = 0; i < 6; i++) {
		GLfloatPoint2D point = generateTrianglePoint(i);
		line[i].x = point.x;
		line[i].y = point.y;
	}

	glLineWidth(3);
}

void myIdle()
{
	//this function will be invoked when idle

	t += 0.001;
	if (t > 1) t = 0;

	// Calculate the current coordinates of the polygyon using interpolation.
	for (int i = 0; i < 6; i++) {

		// Calcuate the triangle and hexagon points in real time.
		// This can also be precalculated in the init() function and stored in global arrays.
		GLfloatPoint2D trianglePoint = generateTrianglePoint(i);
		GLfloatPoint2D hexagonPoint = generateHexagonPoint(i);

		// Interpolate between triangle points and hexagon points
		line[i].x = trianglePoint.x * (1 - t) + hexagonPoint.x * t;
		line[i].y = trianglePoint.y * (1 - t) + hexagonPoint.y * t;
	}

	glutPostRedisplay();
}


//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	Sleep(1);
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
	glBegin(GL_LINE_LOOP);
	//draw shape here
	for (int i = 0; i < 6; i++) {
		glVertex2f(line[i].x, line[i].y);
	}
	glEnd();

	glutSwapBuffers();	// send all output to display
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("Computer Graphics Lab - Animation"); // open the screen window

	glutDisplayFunc(myDisplay);     // register redraw callback function
	glutIdleFunc(myIdle);			// register idle callback function

	myInit();
	glutMainLoop(); 		     // go into a perpetual loop
}


//--------------- setWindow ---------------------
void setWindow(float left, float right, float bottom, float top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

float computeLineLength(GLfloatPoint2D p1, GLfloatPoint2D p2)
{
	return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}