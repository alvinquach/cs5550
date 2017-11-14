#ifndef LAB_CAMERA_H
#define LAB_CAMERA_H

#include "Camera.h"

//Global Variables
const int screenWidth = 960;	   // width of screen window in pixels
const int screenHeight = 540;	   // height of screen window in pixels

GLfloat goldAmbient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
GLfloat goldDiffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
GLfloat goldSpecular[] = { 0.628281f, 0.555802f, 0.366065f, 1.0f };
GLfloat goldShininess[] = { 0.4f * 128 };

GLfloat silverAmbient[] = { 0.19225f, 0.19225f, 0.19225f, 1.0f };
GLfloat silverDiffuse[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f };
GLfloat silverSpecular[] = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
GLfloat silverShininess[] = { 0.4f * 128 };

GLfloat position[] = { 1.5f, 6.0f, 0.0f, 1.0f };
GLfloat lightIntensity[] = { 0.86f, 0.86f, 0.86f, 1.0f };

bool lightAnimation = false;
GLfloat lightAngle = 0.0f;

Camera cam; // global camera object

#endif