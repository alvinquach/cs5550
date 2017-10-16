#include <windows.h>
#include <cmath>
#include "Window.h"

const int Window::ScreenWidth = 960;
const int Window::ScreenHeight = 540;
const int Window::ScreenPositionX = 50;
const int Window::ScreenPositionY = 50;
const float Window::WorldWidth = 10.0;
const float Window::WorldHeight = WorldWidth * ScreenHeight / ScreenWidth;
const float Window::NearZClipPlane = 0.0;
const float Window::FarZClipPlane = 1000.0;
const float Window::FrameRate = 60.0;

void Window::SetWindow() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WorldWidth / 2, WorldWidth / 2, -WorldHeight / 2, WorldHeight / 2, NearZClipPlane, FarZClipPlane);
}