// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#include "Input.h"
#include "Scene.h"

const float Input::InputDelay = 500.0;

void Input::Keyboard(unsigned char key, int mouseX, int mouseY) {

	Robot& robot = Scene::GetRobot();

	switch (key) {

	// Throw ball.
	case 'a':
		robot.enable();
		robot.iThrowPower();
		break;

	// Toggle between turning on and off displaying coordinate system.
	case 'c':		Scene::ToggleShowAxes();		break;

	// Lift up the upper arm.
	case 'i':
		robot.moveUpperArm(1);
		break;

	// Lift down the upper arm.
	case 'I':
		robot.moveUpperArm(-1);
		break;

	// Lift up the lower arm.
	case 'j':
		robot.moveLowerArm(1);
		break;

	// Lift down the lower arm.
	case 'J':
		robot.moveLowerArm(-1);
		break;

	// Open the hand.
	case 'm':
		robot.moveFingers(1);
		break;

	// Close the hand.
	case 'M':
		robot.moveFingers(-1);
		break;

	// Lift up the hand.
	case 'n':
		robot.moveHand(1);
		break;

	// Lift down the hand.
	case 'N':
		robot.moveHand(-1);
		break;

	// Toggle robot deactivation.
	case 'o':
		robot.isDisabled() ? robot.enable() : robot.disable();
		break;

	// Exit the program.
	case 'q':
	case 'Q':
		exit(0);

	// Rotate the entire arm clockwise.
	case 'r':
		robot.rotateBase(1);
		break;

	// Rotate the entire arm counterclockwise.
	case 'R':
		robot.rotateBase(-1);
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

	Robot& robot = Scene::GetRobot();

	switch(key) {

	case GLUT_KEY_UP:
		robot.moveBase(1);
		break;

	case GLUT_KEY_DOWN:
		robot.moveBase(-1);
		break;

	case GLUT_KEY_LEFT:
		robot.rotateBase(-1);
		break;

	case GLUT_KEY_RIGHT:
		robot.rotateBase(1);
		break;

	default:
		break;
	}

}
