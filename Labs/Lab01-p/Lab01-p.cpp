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



//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen 

									  // draw a graph here
	if (choice == 1)
	{
	}
	if (choice == 2)
	{
	}
	if (choice == 3)
	{
	}
	if (choice == 4)
	{
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