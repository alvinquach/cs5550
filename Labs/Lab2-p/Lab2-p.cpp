//Computer Graphics Lab : Drawing an object and changing world view

#include <windows.h>
#include <math.h>	// included for random number generation
#include <gl/Gl.h>
#include "glut.h"
#include <iostream>

const int screenWidth = 500;
const int screenHeight = 500;

///	<summary>Multiplier for zooming in and out.</summary>
const float zoomFactor = 0.8;

///	<summary>Distance to pan the windows when using arrow keys as a percentage of the window dimensions.</summary>
const float panFactor = 0.1;

// left, right, bottom, top
float lt, rt, bt, tp;

// Used to track mouse movement.
int lastX, lastY;

///	<summary>Helper function for zooming in and out.</summary>
///	<param name='factor'>The multiplicative factor to zoom by.</param>
void zoom(float factor) {
	lt *= factor;
	rt *= factor;
	bt *= factor;
	tp *= factor;
}

///	<summary>
///		Helper function for panning the window.
///		Inputs are percentages of the current window dimensions.
///	</summary>
///	<param nam ='x'>The percentage of the current window's width to pan by.</param>
///	<param name='y'>The percentage of the current window's height to pan by.</param>
void pan(float x, float y) {
	float distX = (rt - lt) * x;
	float distY = (tp - bt) * y;
	lt += distX;
	rt += distX;
	bt += distY;
	tp += distY;
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
	glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
	glMatrixMode(GL_PROJECTION); 	   // set "camera shape"
	glLoadIdentity();
	lt = -10;
	rt = 10;
	bt = -10;
	tp = 10;
	gluOrtho2D(lt, rt, bt, tp);	// set the world window
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
	switch (theKey) {
	case 'z':
		// zoom-in
		zoom(zoomFactor);
		break;
	case 'Z':
		// zoom-out
		zoom(1 / zoomFactor);
		break;
	default:
		break;		      // do nothing
	}
	glutPostRedisplay(); // implicitly call myDisplay
}

void myMouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			lastX = x;
			lastY = y;
		}

		// For zooming using mouse wheel.
		// Doesn't work with GLUT 3.7.6 and/or my mouse.
		else if (button == 3) {
			zoom(zoomFactor);
		}
		else if (button == 4) {
			zoom(1 / zoomFactor);
		}
	}
}

void myMotion(int x, int y) {
	float distX = (float)(lastX - x) / screenWidth;
	float distY = (float)(y - lastY) / screenWidth;
	pan(distX, distY);

	lastX = x;
	lastY = y;

	glutPostRedisplay();
}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
	switch (theKey) {
	case GLUT_KEY_UP:
		pan(0, -panFactor);
		break;
	case GLUT_KEY_DOWN:
		pan(0, panFactor);
		break;
	case GLUT_KEY_LEFT:
		pan(panFactor, 0);
		break;
	case GLUT_KEY_RIGHT:
		pan(-panFactor, 0);
		break;
	default:
		break;		      // do nothing
	}

	glutPostRedisplay(); // implicitly call myDisplay
}

//--------------- setWindow ---------------------
void setWindow(float left, float right, float bottom, float top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

	setWindow(lt, rt, bt, tp);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0000, 0.0000);
	glVertex2f(0.0000, 0.4000);
	glVertex2f(0.0898, 0.1236);
	glVertex2f(0.3804, 0.1236);
	glVertex2f(0.1453, -0.0472);
	glVertex2f(0.2351, -0.3236);
	glVertex2f(0.0000, -0.1528);
	glVertex2f(-0.2351, -0.3236);
	glVertex2f(-0.1453, -0.0472);
	glVertex2f(-0.3804, 0.1236);
	glVertex2f(-0.0898, 0.1236);
	glVertex2f(0.0000, 0.4000);
	glEnd();

	//glFlush();
	glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
									//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("Computer Graphics - Lab"); // open the screen window

	glutDisplayFunc(myDisplay);     // register redraw function
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);
	glutSpecialFunc(mySpecialKeyboard);

	myInit();

	glutMainLoop(); 		     // go into a perpetual loop
}