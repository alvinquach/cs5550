// Alvin Quach, 300793745
// CS5550 F17 - HW1 PQ

#include "Draw.h"

float Draw::BallOutlineThickness = 5.0;
float Draw::BallSelectedPulsePeriod = 91.0;
float Draw::BallSelectedMaxOpacity = 0.69;
float Draw::BallGhostOpacity = 0.420;

void Draw::SetWindow(float left, float right, float bottom, float top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void Draw::DrawBall(Ball& ball) {

	// Draw filled style ball.
	if (ball.isFilled()) {
		glBegin(GL_TRIANGLE_FAN);

		// Draw center vertex with highlight color.
		SetGlColor4f(ball.getHighlight(), ball.isSolid() ? 1.0 : BallGhostOpacity);
		glVertex2f(ball.getPosition().getX(), ball.getPosition().getY());

		// Draw rest of ball with ball's actual color.
		SetGlColor4f(ball.getColor(), ball.isSolid() ? 1.0 : BallGhostOpacity);
		for (float t = 0.0; t < 1.0 + 1.0 / Ball::VertexCount; t += 1.0 / Ball::VertexCount) {
			glVertex2f(
				ball.getRadius() * cos(2 * M_PI * t) + ball.getPosition().getX(),
				ball.getRadius() * sin(2 * M_PI * t) + ball.getPosition().getY()
			);
		}
	}

	// Draw outline style ball.
	else {
		glLineWidth(BallOutlineThickness);
		glBegin(GL_LINE_LOOP);
		SetGlColor3f(ball.getColor());
		for (float t = 0.0; t < 1.0; t += 1.0 / Ball::VertexCount) {
			glVertex2f(
				ball.getRadius() * cos(2 * M_PI * t) + ball.getPosition().getX(),
				ball.getRadius() * sin(2 * M_PI * t) + ball.getPosition().getY()
			);
		}
	}

	glEnd();
}

void Draw::DrawSelectedBall(Ball& ball) {
	glLineWidth(BallOutlineThickness);
	glBegin(ball.isFilled() ? GL_POLYGON : GL_LINE_LOOP);

	// Calculate pulse effect based on elapsed time.
	float x = glutGet(GLUT_ELAPSED_TIME) / BallSelectedPulsePeriod;
	glColor4f(
		0.25 * sin((x - 1 * M_PI) / 3) + 0.25,
		0.25 * sin((x - 3 * M_PI) / 3) + 0.25,
		0.25 * sin((x - 5 * M_PI) / 3) + 0.25,
		0.50 * (BallSelectedMaxOpacity * sin(x) + BallSelectedMaxOpacity)
	);

	for (float t = 0.0; t < 1.0; t += 1.0 / Ball::VertexCount) {
		glVertex2f(
			ball.getRadius() * cos(2 * M_PI * t) + ball.getPosition().getX(),
			ball.getRadius() * sin(2 * M_PI * t) + ball.getPosition().getY()
		);
	}
	glEnd();
}

void Draw::SetGlColor3f(ColorRGB& color) {
	glColor3f(color.getFloatR(), color.getFloatG(), color.getFloatB());
}

void Draw::SetGlColor4f(ColorRGB & color, float alpha) {
	glColor4f(color.getFloatR(), color.getFloatG(), color.getFloatB(), alpha);
}
