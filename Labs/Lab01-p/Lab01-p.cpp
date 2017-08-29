// Computer Graphics
// change include file names or paths as needed
#include <windows.h>
#include <math.h>	// included for random number generation
#include <gl/Gl.h>
#include "glut.h"
#include <iostream>
#define PI 3.14159265

using namespace std;

const int screenWidth = 640;
const int screenHeight = 480;

int choice = 0;

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
	glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black  	
	glMatrixMode(GL_PROJECTION); 	   // set "camera shape"
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}

///	<summary>
///		Helper method for inserting verticies that will be centered on the screen.
///	</summary>
///	<param name='x'>The x value of the vertex.</param>
///	<param name='y'>The y value of the vertex.</param>
void insertVertex2d(GLdouble x, GLdouble y) {

	// Use the smaller dimension of the screen as reference.
	GLint dim = min(screenHeight, screenWidth);

	// The amount to translate the graph.
	GLint xShift = screenWidth / 2;
	GLint yShift = screenHeight / 2;

	glVertex2d(x * dim + xShift, y * dim + yShift);
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{

	// Scaling and shifting factors for the sinusoidal waves.
	GLdouble yScale = 0.25;
	GLdouble yShift = 0.5;

	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen 

	// draw a graph here
	if (choice == 1) {
		glBegin(GL_POINTS);
		for (GLdouble x = 0; x < screenWidth; x++) {
			GLdouble x1 = 2 * PI * x / screenWidth;
			GLdouble y = cos(x1);
			glVertex2d(x, screenHeight * (yScale * y + yShift));
		}
		glEnd();
	}

	if (choice == 2) {
		glBegin(GL_POINTS);
		for (GLdouble x = 0; x < screenWidth; x++) {
			GLdouble x1 = 4 * PI * x / screenWidth;
			GLdouble y = cos(x1);
			glVertex2d(x, screenHeight * (yScale * y + yShift));
		}
		glEnd();
	}

	if (choice == 3) {
		glBegin(GL_POINTS);
		for (GLdouble x = 0; x < screenWidth; x++) {
			GLdouble x1 = 6 * PI * x / screenWidth;
			GLdouble y = sin(x1);
			glVertex2d(x, screenHeight * (yScale * y + yShift));
		}
		glEnd();
	}

	if (choice == 4) {
		glBegin(GL_LINE_LOOP);

		// Hard coded.
		insertVertex2d(0.0000, 0.4000);
		insertVertex2d(0.0898, 0.1236);
		insertVertex2d(0.3804, 0.1236);
		insertVertex2d(0.1453, -0.0472);
		insertVertex2d(0.2351, -0.3236);
		insertVertex2d(0.0000, -0.1528);
		insertVertex2d(-0.2351, -0.3236);
		insertVertex2d(-0.1453, -0.0472);
		insertVertex2d(-0.3804, 0.1236);
		insertVertex2d(-0.0898, 0.1236);

		glEnd();
	}

	glFlush();
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("Computer Graphics - Lab"); // open the screen window

	glutDisplayFunc(myDisplay);     // register redraw function


	cout << "Enter an integer (1 -4 ) for your choice : ";
	cin >> choice;

	myInit();

	glutMainLoop(); 		     // go into a perpetual loop
}