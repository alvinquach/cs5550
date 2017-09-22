#include "Draw.h"

void Draw::SetWindow(float left, float right, float bottom, float top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}


void Draw::DrawBall(Ball& ball) {
	glBegin(GL_TRIANGLE_FAN);

	// Draw center vertex with highlight color.
	SetGlColor3f(CalculateHightlightColor(ball.getColor()));
	glVertex2f(ball.getPosition().getX(), ball.getPosition().getY());

	// Draw rest of ball with ball's actual color.
	SetGlColor3f(ball.getColor());
	for (float t = 0; t < 1; t += 1.0 / Ball::VertexCount) {
		glVertex2f(
			ball.getRadius() * cos(2 * M_PI * t) + ball.getPosition().getX(),
			ball.getRadius() * sin(2 * M_PI * t) + ball.getPosition().getY()
		);
	}
	glEnd();
}

void Draw::DrawSelectedBall(Ball& ball) {
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	for (float t = 0; t < 1; t += 1.0 / Ball::VertexCount) {
		glVertex2f(
			(ball.getRadius() + 1) * cos(2 * M_PI * t) + ball.getPosition().getX(),
			(ball.getRadius() + 1) * sin(2 * M_PI * t) + ball.getPosition().getY()
		);
	}
	glEnd();
}


ColorRGB Draw::CalculateHightlightColor(ColorRGB& color) {
	return ColorRGB(
		(color.getR() + 511) / 3,
		(color.getG() + 511) / 3,
		(color.getB() + 511) / 3
	);
}

void Draw::SetGlColor3f(ColorRGB& color) {
	glColor3f(color.getFloatR(), color.getFloatG(), color.getFloatB());
}