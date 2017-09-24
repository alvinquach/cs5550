#include <ctime>
#include "main.h"

using namespace std;

void test() {
	Vector2f a = Vector2f(3, 4);
	Vector2f b = 6.9 * a;

	cout << a.getX() << ", " << a.getY() << endl;
	cout << b.getX() << ", " << b.getY() << endl;
	b.setMagnitude(10);
	cout << b.getX() << ", " << b.getY() << endl;

	Vector2f c = Vector2f(-2.5, 3);
	Vector2f d = Vector2f(2, 5);
	d.setMagnitude(2.44);

	cout << Vector2f::Dot(a + b, c - d) << endl;

	bool exit;
	cout << "Press enter to exit" << endl;
	cin >> exit;

}

void main(int argc, char** argv) {
	init(argc, argv);
}

void init(int argc, char** argv) {

	srand((unsigned)time(0));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(screenPositionX, screenPositionY);
	glutCreateWindow("C5550 - Homework 1 Programming Question");

	// Set up inputs
	glutKeyboardFunc(Input::keyboard);
	glutSpecialFunc(Input::specialKeyboard);

	glutDisplayFunc(display);
	callTimerFunc();

	glClearColor(1, 1, 1, 0);
	Draw::SetWindow(-worldWidth / 2, worldWidth / 2, -worldHeight / 2, worldHeight / 2);
	cout << Scene::GetInstance().GetBalls().size() << endl;

	for (int i = 0; i < 100; i++) {
		cout << Random::RandomFloat(-5.0, 5.0) << endl;
	}

	glutMainLoop();
}

void display() {

	//Sleep(1000 / Physics::UpdateRate);
	glClear(GL_COLOR_BUFFER_BIT);
	
	for (int i = 0; i < (int)Scene::GetInstance().GetBalls().size(); i++) {
		Draw::DrawBall(Scene::GetInstance().GetBalls()[i]);
	}

	Ball *selectedBall = Scene::GetSelectedBall();
	if (selectedBall) {
		Draw::DrawSelectedBall(*selectedBall);
	}

	glutSwapBuffers();	// send all output to display
}

void timer(int value) {

	// Keeps track of how many physics frames have been calcuated.
	static long physicsFrames;

	// Update position for each ball.
	for (int i = 0; i < Scene::GetInstance().GetBalls().size(); i++) {
		Physics::UpdateBalls(Scene::GetInstance().GetBalls());
	}

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