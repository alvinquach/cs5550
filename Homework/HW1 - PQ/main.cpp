#include "main.h"

using namespace std;

Ball ball;

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

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(screenPositionX, screenPositionY);
	glutCreateWindow("C5550 - Homework 1 Programming Question");

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glClearColor(1, 1, 1, 0);
	Draw::SetWindow(-worldWidth / 2, worldWidth / 2, -worldHeight / 2, worldHeight / 2);

	ball = Ball();
	ball.setColor(ColorRGB(0, 64, 255));
	ball.setVelocity(Vector2f(6, 9));

	glutMainLoop();
}

void display() {

	Sleep(1000 / Physics::UpdateRate);
	glClear(GL_COLOR_BUFFER_BIT);
	
	Draw::DrawBall(ball);

	glutSwapBuffers();	// send all output to display
}

void idle() {
	Physics::UpdateBall(ball);
	//Vector2f deltaPosition = Vector2f(
	//	ball.getVelocity().getX() * Physics::DeltaTime,
	//	ball.getVelocity().getY() * Physics::DeltaTime
	//);
	//ball.setPosition(ball.getPosition() + deltaPosition);
	glutPostRedisplay();
}