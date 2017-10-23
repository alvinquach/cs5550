// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#include "Input.h"
#include "Scene.h"

const float Input::InputDelay = 500.0;

void Input::Keyboard(unsigned char key, int mouseX, int mouseY) {

	switch (key) {

	// Throw ball.
	case 'a':
		Scene::EnableRobot();
		// TODO Throw ball.
		break;

	// Toggle between turning on and off displaying coordinate system.
	case 'c':		Scene::ToggleShowAxes();		break;

	// Lift up the upper arm.
	case 'i':
		if (!Scene::IsRobotDisabled()) {
			Scene::GetRobot().moveUpperArm(1);
		}
		break;

	// Lift down the upper arm.
	case 'I':
		if (!Scene::IsRobotDisabled()) {
			Scene::GetRobot().moveUpperArm(-1);
		}
		break;

	// Lift up the lower arm.
	case 'j':
		if (!Scene::IsRobotDisabled()) {
			Scene::GetRobot().moveLowerArm(1);
		}
		break;

	// Lift down the lower arm.
	case 'J':
		if (!Scene::IsRobotDisabled()) {
			Scene::GetRobot().moveLowerArm(-1);
		}
		break;

	// Open the hand.
	case 'm':
		if (!Scene::IsRobotDisabled()) {
			// TODO Implement this.
		}
		break;

	// Close the hand.
	case 'M':
		if (!Scene::IsRobotDisabled()) {
			// TODO Implement this.
		}
		break;

	// Lift up the hand.
	case 'n':
		if (!Scene::IsRobotDisabled()) {
			// TODO Implement this.
		}
		break;

	// Lift down the hand.
	case 'N':
		if (!Scene::IsRobotDisabled()) {
			// TODO Implement this.
		}
		break;

	// Toggle robot deactivation.
	case 'o':
		Scene::IsRobotDisabled() ? Scene::EnableRobot() : Scene::DisableRobot();
		break;

	// Exit the program.
	case 'q':
	case 'Q':
		exit(0);

	// Rotate the entire arm clockwise.
	case 'r':
		if (!Scene::IsRobotDisabled()) {
			Scene::GetRobot().rotateBase(1);
		}
		break;

	// Rotate the entire arm counterclockwise.
	case 'R':
		if (!Scene::IsRobotDisabled()) {
			Scene::GetRobot().rotateBase(-1);
		}
		break;

	// Animate the camera
	case 's':
		Scene::GetCamera().toggleAnimation();
		break;

	// Toggle between displaying wireframe and solid models.
	case 'u':
		Scene::ToggleRenderMode();
		break;

	// Zoom out
	case 'z':
		Scene::GetCamera().zoomOut();
		break;

	// Zoom out
	case 'Z':
		Scene::GetCamera().zoomIn();
		break;

	// Reset the scene.
	case 27:
		Scene::Reset();
		break;

	default:
		break;
	}
}

void Input::SpecialKeyboard(int key, int mouseX, int mouseY) {

	switch(key) {

	case GLUT_KEY_UP:
		if (!Scene::IsRobotDisabled()) {
			Scene::GetRobot().moveBase(1);
		}
		break;

	case GLUT_KEY_DOWN:
		if (!Scene::IsRobotDisabled()) {
			Scene::GetRobot().moveBase(-1);
		}
		break;

	case GLUT_KEY_LEFT:
		if (!Scene::IsRobotDisabled()) {
			Scene::GetRobot().rotateBase(-1);
		}
		break;

	case GLUT_KEY_RIGHT:
		if (!Scene::IsRobotDisabled()) {
			Scene::GetRobot().rotateBase(1);
		}
		break;

	default:
		break;
	}

}
