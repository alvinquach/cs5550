// Alvin Quach, 300793745
// CS5550 F17 - HW3 PQ

#include <windows.h>
#include "glut.h"

#include "Camera.h"

#include "Window.h"

const string Window::WindowName = "CS5550 - Homework 2 Programming - by Alvin Quach";
const float Window::ScreenWidth = 960.0;
const float Window::ScreenHeight = 540.0;
const int Window::ScreenPositionX = 50;
const int Window::ScreenPositionY = 50;
const float Window::FrameRate = 60.0;

void Window::SetWindow() {
	glutInitWindowSize(ScreenWidth, ScreenHeight);
	glutInitWindowPosition(ScreenPositionX, ScreenPositionY);
	glutCreateWindow(WindowName.c_str());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-WorldWidth / 2, WorldWidth / 2, -WorldHeight / 2, WorldHeight / 2, NearZClipPlane, FarZClipPlane);
	gluPerspective(Camera::FieldOfView, ScreenWidth / ScreenHeight, Camera::NearZClipPlane, Camera::FarZClipPlane);
}