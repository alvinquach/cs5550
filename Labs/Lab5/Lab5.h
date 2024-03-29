#ifndef LAB_SOLAR_H
#define LAB_SOLAR_H


#define PI 3.1415


//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels

const float worldWidth = 500.0;
const float worldHeight = 500.0;

// Initial values
GLdouble scale = 1.0;
GLdouble tx = 0.0, ty = 0.0, tz = 0.0;
GLdouble rotation_angle = 0.0;

// global values for camera
GLdouble eyex = 25.0, eyey = 25.0, eyez = 25.0;
GLdouble lookx = 0.0, looky = 0.0, lookz = 0.0;

int view = 0;

// global values for shading
GLfloat ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat shininess[] = { 50.0f };

GLfloat position[] = { 2.0f, 6.0f, 3.0f, 0.0f };
GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };

// added variables
GLdouble t = 0.0;
GLdouble speedMultiplier = 420.0;
GLdouble periodSunDay = 24.0; // At equator
GLdouble periodEarthDay = 1.00;
GLdouble periodEarthOrbital = 365.25;
GLdouble periodMoonDay = 27.3;
GLdouble periodMoonOrbital = 27.3;
GLdouble periodMarsDay = 1.03;
GLdouble periodMarsOrbital = 687.0;

bool rotateCamera = false;
GLdouble tCamera = 0.0;
GLdouble cameraRadius1 = 55.90;
GLdouble cameraRadius2 = 27.95;
GLdouble cameraInitialAngle = 1.107;
GLdouble periodCameraOrbital = 0.69;

#endif