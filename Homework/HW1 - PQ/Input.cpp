// Alvin Quach, 300793745
// CS5550 F17 - HW1 PQ

#include "Input.h"
#include "Scene.h"
#include "Window.h"
#include "glut.h"

const float Input::BallRadiusDeltaAmount = 0.2;
const float Input::BallSpeedDeltaAmount = 1.337;

void Input::Mouse(int button, int state, int x, int y) {

	vector<Ball>& balls = Scene::GetBalls();
	Vector2f worldCoordinates = ConvertScreenToWorld(Vector2f(x, y));

	if (state == GLUT_DOWN && (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON)) {

		// If the mouse click was on a ball, then select the ball.
		for (int i = 0; i < balls.size(); i++) {
			Ball& ball = balls[i];
			if (Vector2f::Distance(ball.getPosition(), worldCoordinates) <= ball.getRadius()) {
				Scene::SelectBall(i);
					
				// Also 'lock' the ball if it was a left click
				if (button == GLUT_LEFT_BUTTON) {
					Scene::LockBall(i);
				}

				break;
			}
		}

	}

	// Unlock the 'locked' ball if left button was released.
	else if (button = GLUT_LEFT_BUTTON) {
		Scene::LockBall(-1);
	}

}

void Input::Motion(int x, int y) {

}

void Input::Keyboard(unsigned char key, int mouseX, int mouseY) {

	Ball *selectedBall = Scene::GetSelectedBall();

	switch (key) {

	// Add ball. There is a limit of how many balls can be added.
	case 'a':
		if (Scene::GetInstance().GetBalls().size() < 5) {
			Scene::AddBall();
		}
		break;

	// Reset the scene.
	case 'n':
		Scene::Reset();
		break;

	// Toggles between a filled ball and a non-filled ball.
	case 'p':
		if (selectedBall) {
			selectedBall->toggleFilled();
		}
		break;

	// Remove the most recently added ball of the scene. This will not remove the last ball.
	case 'r':
		if (Scene::GetInstance().GetBalls().size() > 1) {
			Scene::RemoveLastBall();
		}
		break;

	// Select a ball. '0' deselects the ball.
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
		Scene::SelectBall(key - '0' - 1);
		break;

	default:
		break;
	}

}

void Input::SpecialKeyboard(int key, int mouseX, int mouseY) {

	Ball *selectedBall = Scene::GetSelectedBall();

	switch (key) {

	// Increase radius. Velocity will be decreased to preserve momentum.
	case GLUT_KEY_PAGE_UP:
		if (selectedBall) {
			selectedBall->setRadius(selectedBall->getRadius() + BallRadiusDeltaAmount, true);
		}
		break;

	// Decrease radius. Velocity will be increased to preserve momentum.
	case GLUT_KEY_PAGE_DOWN:
		if (selectedBall) {
			selectedBall->setRadius(selectedBall->getRadius() - BallRadiusDeltaAmount, true);
		}
		break;

	// Increase radius. Velocity will be decreased to preserve momentum.
	case GLUT_KEY_UP:
		if (selectedBall) {
			selectedBall->setSpeed(selectedBall->getSpeed() + BallSpeedDeltaAmount);
		}
		break;

	case GLUT_KEY_DOWN:
		if (selectedBall) {
			selectedBall->setSpeed(selectedBall->getSpeed() - BallSpeedDeltaAmount);
		}
		break;

	default:
		break;
	}
}

Vector2f& Input::ConvertScreenToWorld(Vector2f& screenCoordinates) {
	return Vector2f(
		worldWidth / screenWidth * screenCoordinates.getX() - worldWidth / 2,
		-worldHeight / screenHeight * screenCoordinates.getY() + worldHeight / 2
	);
}
