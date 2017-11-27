#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>  //suitable when using Windows 95/98/NT
#include <gl/gl.h>
#include <gl/glu.h>
#include "glut.h"

#include "Main.h"

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// TODO Change these to use variables.
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Lab - Manipulate a camera around a teapot");

	glEnable(GL_DEPTH_TEST);

	// Register callback functions
	glutDisplayFunc(display);

	glutMainLoop();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Draw::DrawAxes();
	glutSwapBuffers();
}