//Computer Graphics Lab - Animation
#include <windows.h>
#include <iostream>
#include <cmath>
#include <gl/Gl.h>
#include "glut.h"

#include "Lab3.h"

using namespace std;

void myInit(void)
 {
    glClearColor(1.0,1.0,1.0,0.0);      // background color is white
    glColor3f(0.0f, 0.0f, 1.0f);        // drawing color is blue

 	setWindow(-worldWidth/2, worldWidth/2, -worldHeight/2, worldHeight/2); // set the world window

	line[0].x = 0;
	line[0].y = 0;
	line[1].x = 100;
	line[1].y = 0;
	lineLength = computeLineLength(line[0], line[1]);

	glLineWidth(3);
}

void myIdle()
{
	//this function will be invoked when idle

	t += 0.001;
	if(t >1) t=0;


	line[1].x = lineLength * cos(2*PI*t);
	line[1].y = lineLength * sin(2*PI*t);

	glutPostRedisplay();
}


//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	Sleep(1);
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
	glBegin(GL_LINES);
	//draw shape here
		glVertex2f(line[0].x, line[0].y);
		glVertex2f(line[1].x, line[1].y);
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