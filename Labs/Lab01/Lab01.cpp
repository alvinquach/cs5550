// Computer Graphics

// change accordingly
#include <windows.h>
#include <math.h>	// included for random number generation
#include <gl/Gl.h>
#include "glut.h"
#define PI 3.14159265

const int screenWidth = 500;
const int screenHeight = 500;

struct GLintPoint {
	GLint x, y;
};

GLintPoint pts[4];
int NoOfPts = 0;
int pointIndex = 0;
bool drawRect = true;
bool resetRectOnNextClick = false;

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
	glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
	glMatrixMode(GL_PROJECTION); 	   // set "camera shape"
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}

///	<summary>Helper method for resetting polygon point counters.</summary>
void resetPointCount() {
	NoOfPts = 0;
	pointIndex = 0;
	resetRectOnNextClick = false;
}

/// <summary>Helper method for generating a random float between 0.0 and 1.0.</summary>
float randomFloat() {
	return (float)rand() / RAND_MAX;
}

/// <summary>Helper method for drawing the rectangle.</summary>
void drawRectangle(GLenum mode) {
	glBegin(mode);
	for (int i = 0; i < NoOfPts; i++) {
		glVertex2d(pts[i].x, pts[i].y);
	}
	glEnd();
}

void myMouse(int button, int state, int x, int y)
{
	// Only do something if only the left or right button was pushed down (don't do anything if button was released).
	if (state != GLUT_DOWN || (button != GLUT_LEFT_BUTTON && button != GLUT_RIGHT_BUTTON)) {
		return;
	}

	// Reset point count and point index on this click if needed.
	if (resetRectOnNextClick) {
		resetPointCount();
	}

	// Set point based on mouse coordinates.
	pts[pointIndex].x = x;
	pts[pointIndex].y = screenHeight - y;

	// If the point index exceeds 3, then wrap it back to 0.
	if (++pointIndex > 3) {
		pointIndex = 0;
	}

	// Increment number of points by one if it is less than 4.
	NoOfPts += NoOfPts < 4 ? 1 : 0;

	// If right clicked, reset point count and point index on next click.
	if (button == GLUT_RIGHT_BUTTON) {
		resetRectOnNextClick = true;
	}

	drawRect = true;
	glutPostRedisplay();
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
	switch (theKey) {
	case 'c':
		glClearColor(randomFloat(), randomFloat(), randomFloat(), 1.0);
		break;
	case 'p':
		drawRect = false;
		resetPointCount();
		break;
	default:
		break;		      // do nothing
	}

	glutPostRedisplay(); // implicitly call myDisplay
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

	// Draw polygon
	if (drawRect) {
		drawRectangle(GL_POLYGON);

		// Not required.
		drawRectangle(GL_POINTS);
		drawRectangle(GL_LINE_LOOP);
	}

	// Draw cosine
	else {
		glBegin(GL_POINTS);
		for (GLdouble x = 0; x < screenWidth; x++) {
			GLdouble x1 = 2 * PI * x / screenWidth;
			GLdouble y = cos(x1);
			glVertex2d(x, screenHeight * (0.25 * y + 0.5));
		}
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
	glutCreateWindow("Computer Graphics - Lab1"); // open the screen window

	glutDisplayFunc(myDisplay);     // register redraw function
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);

	myInit();

	glutMainLoop(); 		     // go into a perpetual loop
}



/* C++ code segment to generate random numbers: between 1 and 50

#include <ctime>

...

srand((unsigned)time(0));
int randomInt = rand()%50 + 1;
float randomFloat = (float)rand()/RAND_MAX;
cout << "Random Integer between 1 and 50 = " << randomInt << endl;
cout << "Random Float between 0 and 1 = " << randomFloat << endl;
*/