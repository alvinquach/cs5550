//Computer Graphics Lab : Drawing an object and changing world view

#define _USE_MATH_DEFINES
#include <windows.h>
#include <math.h>	// included for random number generation
#include <gl/Gl.h>
#include "glut.h"
#include <iostream>
#include <string>

using namespace std;

const int screenWidth = 500;
const int screenHeight = 500;

///	<summary>How many vertices to use when drawing the ellipse.</summary>
const int vertexCount = 256;

///	<summary>Multiplier for zooming in and out.</summary>
const float zoomFactor = 0.8;

///	<summary>Distance to pan the windows when using arrow keys as a percentage of the window dimensions.</summary>
const float panFactor = 0.1;

/// <summary>The width of the ellipse.</summary>
float radius1 = 1.0;

/// <summary>The height of the ellipse.</summary>
float radius2 = 1.0;

///	<summary>Multiplier used when increasing or decreasing the radii.</summary>
const float radiusChangeFactor = 0.9;

/// <summary>Whether to render the polygon using points or using line-loop.</summary>
int outlineStyle = 0;

/// <summary>Whether to render the polygon using points or using line-loop.</summary>
float outlineSize = 2.0;

// left, right, bottom, top
float lt, rt, bt, tp;

// Used to track mouse movement.
int lastX, lastY;

///	<summary>Helper function for zooming in and out.</summary>
///	<param name='factor'>The multiplicative factor to zoom by.</param>
void zoom(float factor) {

	// Find horizontal and vertical midpoints of current window relative to the world.
	float midX = (lt + rt) / 2;
	float midY = (tp + bt) / 2;

	// Zoom about the window midpoint.
	lt = (lt - midX) * factor + midX;
	rt = (rt - midX) * factor + midX;
	bt = (bt - midY) * factor + midY;
	tp = (tp - midY) * factor + midY;
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

	// Zoom in
	case 'z':
		zoom(zoomFactor);
		break;

	// Zoom out
	case 'Z':
		zoom(1 / zoomFactor);
		break;

	// Toggle outline style
	case 't':
	case 'T':
		outlineStyle = !outlineStyle;
		break;

	// Increase object size
	case '+':
		radius1 /= radiusChangeFactor;
		radius2 /= radiusChangeFactor;
		break;

	// Decrease object size
	case '-':
		radius1 *= radiusChangeFactor;
		radius2 *= radiusChangeFactor;
		break;

	// Increase object outline thickness
	case 'b':
		outlineSize++;
		break;

	// Decrease object outline thickness
	case 'B':
		outlineSize -= outlineSize > 1 ? 1 : 0;
		break;
	
	// Do nothing...
	default:
		break;
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


///	<summary>Helper function for drawing the ellipse.</summary>
void drawEllipse() {
	if (outlineStyle) {
		glLineWidth(outlineSize);
		glBegin(GL_LINE_LOOP);
	}
	else {
		glPointSize(outlineSize);
		glBegin(GL_POINTS);
	}
	for (float t = 0; t < 1; t += 1.0 / vertexCount) {
		glVertex2f(radius1 * cos(2 * M_PI * t), radius2 * sin(2 * M_PI * t));
	}
	glEnd();
}


//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

	setWindow(lt, rt, bt, tp);

	drawEllipse();

	glutSwapBuffers();
}

void showPrompt() {
	while (true) {
		string input;
		cout << "1. Drawing a circle" << endl << "2. Drawing an ellipse" << endl << "Choose 1 or 2: ";
		cin >> input;

		// If input was valid...
		if (!input.compare("1") || !input.compare("2")) {

			// Ask for radius or width and height depending on the choice.
			// No error handling for these inputs due to lazyness.
			if (!input.compare("1")) {
				cout << "Enter a radius for the circle: ";
				cin >> radius1;
				radius2 = radius1; // A circle is basically an ellipse with the same width and height;
			}
			else if (!input.compare("2")) {
				cout << "Enter the width of the ellipse: ";
				cin >> radius1;
				cout << "Enter the height of the ellipse: ";
				cin >> radius2;
			}

			break; // Choice was valid, so break out of the loop.
		}
		cout << "Invalid choice." << endl << endl;
	}
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

	showPrompt();	// Display user input prompt.

	myInit();

	glutMainLoop(); 		     // go into a perpetual loop

}