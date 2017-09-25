// Alvin Quach, 300793745
// CS5550 F17 - HW1 PQ

#include "main.h"

using namespace std;

string windowName = "CS5550 - Homework 1 Programming - by Alvin Quach";

void main(int argc, char** argv) {
	init(argc, argv);
}

void init(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(screenPositionX, screenPositionY);
	glutCreateWindow(windowName.c_str());

	// Enable alpha blending.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set up inputs
	glutMouseFunc(Input::Mouse);
	glutMotionFunc(Input::Motion);
	glutKeyboardFunc(Input::Keyboard);
	glutSpecialFunc(Input::SpecialKeyboard);

	glutDisplayFunc(display);
	callTimerFunc();

	glClearColor(1, 1, 1, 0);
	Draw::SetWindow(-worldWidth / 2, worldWidth / 2, -worldHeight / 2, worldHeight / 2);

	glutMainLoop();
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	
	for (int i = 0; i < (int)Scene::GetInstance().GetBalls().size(); i++) {
		Draw::DrawBall(Scene::GetInstance().GetBalls()[i]);
	}

	Ball *selectedBall = Scene::GetSelectedBall();
	if (selectedBall) {
		Draw::DrawSelectedBall(*selectedBall);
	}

	Physics::SampleLockedBallPosition();

	glutSwapBuffers();	// send all output to display
}

void timer(int value) {

	// Keeps track of how many physics frames have been calcuated.
	static long physicsFrames;

	// Update position for each ball.
	Physics::UpdateBalls();

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