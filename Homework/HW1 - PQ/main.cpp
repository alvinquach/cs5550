#include <windows.h>
#include <iostream>
#include <cmath>
#include <gl/Gl.h>
#include "glut.h"
#include "ball.h"

using namespace std;

void drawBall(GLenum mode, Ball ball) {
	glBegin(mode);
}

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
	test();
}