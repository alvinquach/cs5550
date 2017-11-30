#define _USE_MATH_DEFINES
#include <windows.h>  //suitable when using Windows 95/98/NT
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "glut.h"

#include"Input.h"
#include "Window.h"

#include "Main.h"

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	Window::SetWindow();

	Camera::LookAt(Vector3f(6.9f, 6.9f, 6.9f), Vector3f::Zero());

	// Register callback functions
	glutMouseFunc(Input::Mouse);
	glutMotionFunc(Input::Motion);
	glutPassiveMotionFunc(Input::Motion);
	glutKeyboardFunc(Input::Keyboard);
	glutSpecialFunc(Input::SpecialKeyboard);
	glutDisplayFunc(display);
	
	callTimerFunc();

	glutMainLoop();
}

void display(void) {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHT0);
	Draw::DrawAxes();
	Draw::DrawGrid(Input::GridMode);
	Draw::DrawTestObject();
	glutSwapBuffers();
}

void timer(int value) {
	Camera::Update(value);
	glutPostRedisplay();

	callTimerFunc();
}

void callTimerFunc() {
	// Using timer instead of idle to be able to control frame rate.
	float deltaTime = 1000 / Window::FrameRate;
	glutTimerFunc(deltaTime, timer, deltaTime);
}