#define _USE_MATH_DEFINES

#include <windows.h>  //suitable when using Windows 95/98/NT
#include <gl/Gl.h>
#include <gl/Glu.h>
#include "glut.h"
#include <iostream>
#include <math.h>

#include "Lab5.h"


void myInit(int shadingChoice, int colorChoice)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	if (shadingChoice == 0) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	}
	else if (shadingChoice == 1) {
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	}

	if (colorChoice == 1) {
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
	}


	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // background is white

	glMatrixMode(GL_PROJECTION); // set the view volume shape
	glLoadIdentity();
	glOrtho(-3.5*worldWidth / worldHeight, 3.5*worldWidth / worldHeight, -3.5, 3.5, 0.1, 100);
}

void myIdle() {

	t += speedMultiplier * 60.0 / 1000;

	// UpdateCamera
	if (view == 0) {
		tCamera += rotateCamera ? 60.0 / 1000 : 0.0;
		eyex = cameraRadius1 * cos(tCamera / periodCameraOrbital * M_PI / 180 + cameraInitialAngle);
		eyey = 25;
		eyez = cameraRadius2 * sin(tCamera / periodCameraOrbital * M_PI / 180 + cameraInitialAngle);
	}
	else if (view == 1) {
		eyex = 25;
		eyey = 0;
		eyez = 0;
	}
	else if (view == 2) {
		eyex = 0;
		eyey = 25;
		eyez = 25;
	}

	glutPostRedisplay();

}


void drawAxes()
{
	glBegin(GL_LINES);
	//x
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(100, 0, 0);
	//y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100, 0);
	//z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100);
	glEnd();
}

void drawEarthOrbit()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 64; i++) {
		glVertex3f(2 * cos(2 * M_PI * i / 64), 0, 2 * sin(2 * M_PI * i / 64));
	}
	glEnd();
}

void drawSun()
{	// Sun
	glColor3f(1.0f, 0.5f, 0.0f);    // sun is orange
	glPushMatrix();
	glRotated(t / periodSunDay, 0.0, 1.0, 0.0);
	glutSolidSphere(0.5, 20, 16);	// locate the sun at the origin
	glPopMatrix();
}


void drawEarthAndMoon()
{
	// Earth
	glColor3f(0.0f, 1.0f, 0.0f); // earth is green
	glPushMatrix();
	glRotated(t / periodEarthOrbital, 0.0, 1.0, 0.0);
	glTranslated(0, 0, 2);

	// We can reuse the above transformations for the moon,
	// so push another matrix here.
	glPushMatrix();
	
	glRotated(t / periodEarthDay, 0.0, 1.0, 0.0);
	glutSolidSphere(0.2, 20, 8);
	glPopMatrix();

	// Moon. Two transformations were carried over from the earth.
	glColor3f(0.5f, 0.5f, 0.5f);
	glPushMatrix();
	glRotated(t / periodMoonOrbital, 0.0, 1.0, 0.0);
	glTranslated(0, 0, 0.3);
	glRotated(t / periodMoonDay, 0.0, 1.0, 0.0);
	glutSolidSphere(0.05, 10, 4);
	glPopMatrix();
	glPopMatrix();
}

void drawMars()
{
	// Mars
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glRotated(t / periodMarsOrbital, 0.0, 1.0, 0.0);
	glTranslated(0, 0, 3);
	glRotated(t / periodMarsDay, 0.0, 1.0, 0.0);
	glutSolidSphere(0.15, 20, 8);
	glPopMatrix();
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displaySolarSystem()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the screen
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, 0.0, 1.0, 0.0);

	drawAxes();
	drawEarthOrbit();
	drawSun();
	drawEarthAndMoon();
	drawMars();

	glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
		rotateCamera = !rotateCamera;
		break;
	case 'v':
		view++;
		view %= 3;
		break;
	default:
		break;
	}

	glutPostRedisplay();

}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Inner Solar System"); // open the screen window


	int shadingChoice = 0;
	int colorChoice = 0;
	std::cout << "Enter Shading Choice (0 for Diffuse, 1 for Specular):\n";
	std::cin >> shadingChoice;

	std::cout << "Enter Color Option (0 for No Color, 1 for Color):\n";
	std::cin >> colorChoice;

	myInit(shadingChoice, colorChoice);

	glutDisplayFunc(displaySolarSystem);
	glutKeyboardFunc(myKeyboard);

	glutIdleFunc(myIdle);

	glutMainLoop();

	return(0);
}