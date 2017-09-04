//Computer Graphics Lab : Drawing an object and changing world view

#include <windows.h>
#include <math.h>	// included for random number generation
#include <gl/Gl.h>
#include "glut.h"
#include <iostream>

const int screenWidth = 500;
const int screenHeight = 500;

// Multiplier for zooming in and out.
const float zoomFactor = 0.8;

// left, right, bottom, top
float lt, rt, bt, tp;

// Used to track mouse movement.
int lastX, lastY;

///	<summary>Helper method for zooming in and out.</summary>
///	<param name='in'>If true, then zoom in. Else, zoom out.</param>
void zoom(bool in) {
	if (in) {
		lt *= zoomFactor;
		rt *= zoomFactor;
		bt *= zoomFactor;
		tp *= zoomFactor;
	}
	else {
		lt /= zoomFactor;
		rt /= zoomFactor;
		bt /= zoomFactor;
		tp /= zoomFactor;
	}
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
		zoom(true);
		break;
	case 'Z':
		// zoom-out
		zoom(false);
		break;
	default:
		break;		      // do nothing
	}
	glutPostRedisplay(); // implicitly call myDisplay
}

void myMouse(int button, int state, int x, int y) {
	std::cout << button << std::endl;
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			lastX = x;
			lastY = y;
		}

		// For zooming using mouse wheel.
		// Doesn't work with GLUT 3.7.6 and/or my mouse.
		else if (button == 3) {
			zoom(true);
		}
		else if (button == 4) {
			zoom(false);
		}
	}
}

void myMotion(int x, int y) {
	double diffX = lastX - x;
	double distX = (diffX / screenWidth) * (rt - lt);
	rt += distX;
	lt += distX;

	double diffY = y - lastY;
	double distY = (diffY / screenHeight) * (tp - bt);
	tp += distY;
	bt += distY;

	lastX = x;
	lastY = y;

	glutPostRedisplay();
}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
	double dist;
	switch (theKey) {
	case GLUT_KEY_UP:
		dist = (tp - bt) * 0.1;
		bt -= dist;
		tp -= dist;
		break;
	case GLUT_KEY_DOWN:
		dist = (tp - bt) * 0.1;
		bt += dist;
		tp += dist;
		break;
	case GLUT_KEY_LEFT:
		dist = (rt - lt) * 0.1;
		lt += dist;
		rt += dist;
		break;
	case GLUT_KEY_RIGHT:
		dist = (rt - lt) * 0.1;
		lt -= dist;
		rt -= dist;
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