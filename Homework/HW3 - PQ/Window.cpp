// Alvin Quach, 300793745
// CS5550 F17 - HW3 PQ

#include <windows.h>
#include "glut.h"

#include "Camera.h"

#include "Window.h"

const string Window::WindowName = "CS5550 - Homework 3 Programming - by Alvin Quach";
const float Window::ScreenWidth = 960.0;
const float Window::ScreenHeight = 720.0;
const int Window::ScreenPositionX = 500;
const int Window::ScreenPositionY = 300;
const float Window::FrameRate = 60.0;

void Window::SetWindow() {
	glutInitWindowSize(ScreenWidth, ScreenHeight);
	glutInitWindowPosition(ScreenPositionX, ScreenPositionY);
	glutCreateWindow(WindowName.c_str());

	glMatrixMode(GL_PROJECTION);
	glClearColor(0.22f, 0.22f, 0.22f, 0.0f); // Same background color as blender.
	glLoadIdentity();
	gluPerspective(Camera::FieldOfView, ScreenWidth / ScreenHeight, Camera::NearZClipPlane, Camera::FarZClipPlane);
}