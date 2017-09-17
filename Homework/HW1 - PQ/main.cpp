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
	Vector2f b = 5 * a;

	cout << a.getX() << ", " << a.getY() << endl;
	cout << b.getX() << ", " << b.getY() << endl;

}

void main(int argc, char** argv) {
	test();
}