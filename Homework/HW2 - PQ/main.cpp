// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#include "main.h"

using std::string;

string windowName = "CS5550 - Homework 2 Programming - by Alvin Quach";

// global values for shading
GLfloat ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat shininess[] = { 50.0f };

GLfloat position[] = { 2.0f, 6.0f, 3.0f, 0.0f };
GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };

GLdouble eyex = 25.0, eyey = 25.0, eyez = 25.0;
GLdouble lookx = 0.0, looky = 0.0, lookz = 0.0;

void main(int argc, char** argv) {
	init(argc, argv);
}

void init(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(Window::ScreenWidth, Window::ScreenHeight);
	glutInitWindowPosition(Window::ScreenPositionX, Window::ScreenPositionY);
	glutCreateWindow(windowName.c_str());

	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Black background.
	glClearColor(0, 0, 0, 0);

	Window::SetWindow();

	glutKeyboardFunc(Input::Keyboard);
	glutSpecialFunc(Input::SpecialKeyboard);

	glutDisplayFunc(display);
	callTimerFunc();

	glutMainLoop();

}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera& camera = Scene::GetCamera();
	camera.updateAnimation(1000 / 60, Vector3f::Zero());

	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	camera.lookAt();

	// Need to disable lighting to draw axes with color.
	glDisable(GL_LIGHTING);

	// Draw Axes
	// TODO Add a variable and if-statement to toggle this.
	Draw::DrawAxes();

	// Reenable lighting after drawing axes.
	glEnable(GL_LIGHTING);

	GLenum renderMode = Scene::GetRenderMode();
	Draw::DrawFloor(renderMode);
	Draw::DrawRobot(renderMode);


	glutSwapBuffers();
}

void timer(int value) {

	// Keeps track of how many physics frames have been calcuated.
	static long physicsFrames;

	Physics::Update();

	// Call the display function only when enough physics recalculations have been performed.
	if (physicsFrames++ % Physics::UpdatesPerFrame == 0) {
		glutPostRedisplay();
	}

	callTimerFunc();
}

void callTimerFunc() {
	// Using timer instead of idle to be able to control frame rate.
	glutTimerFunc(1000 * Physics::DeltaTime, timer, 0);
}