#include <windows.h>
#include <cmath>
#include <gl/Gl.h>
#include "glut.h"
#include "Window.h"

const float Window::ScreenWidth = 960.0;
const float Window::ScreenHeight = 540.0;
const int Window::ScreenPositionX = 50;
const int Window::ScreenPositionY = 50;
const float Window::FieldOfView = 30.0;
const float Window::NearZClipPlane = 0.1;
const float Window::FarZClipPlane = 100.0;
const float Window::FrameRate = 60.0;

void Window::SetWindow() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-WorldWidth / 2, WorldWidth / 2, -WorldHeight / 2, WorldHeight / 2, NearZClipPlane, FarZClipPlane);
	gluPerspective(FieldOfView, ScreenWidth / ScreenHeight, NearZClipPlane, FarZClipPlane);
}