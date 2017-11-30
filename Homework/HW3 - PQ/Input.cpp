// Alvin Quach, 300793745
// CS5550 F17 - HW3 PQ

#include <iostream>
#include "glut.h"

#include "Camera.h"
#include "Draw.h"
#include "Utils.h"

#include "Input.h"

using std::cout;
using std::endl;

// Initialize variables
int Input::Modifiers = 0;
int Input::ActiveButton = -1;
Vector2f Input::InitialMouseCoordinates = Vector2f::Zero();
Vector2f Input::LastMouseCoordinates = Vector2f::Zero();

void Input::Mouse(int button, int state, int x, int y) {
	float* m = Utils::test();
	cout << "Mouse Input: (" << button << ", " << state << ", " << x << ", " << y << ")" << endl;
	if (state == GLUT_DOWN && ActiveButton < 0) {
		if (button == GLUT_MIDDLE_BUTTON) {
			Modifiers = glutGetModifiers();
		}
		ActiveButton = button; // Set active button.
		LastMouseCoordinates = InitialMouseCoordinates = Vector2f(x, y);
		Camera::Interrupt();
	}
	else if (state == GLUT_UP) {
		if (button == GLUT_MIDDLE_BUTTON) {
			Modifiers = 0;
		}
		if (button == ActiveButton) {
			ActiveButton = -1; // Reset active button.
			LastMouseCoordinates = InitialMouseCoordinates = Vector2f::Zero();
		}
	}
}

void Input::Motion(int x, int y) {
	if (ActiveButton == GLUT_MIDDLE_BUTTON) {
		float deltaX = x - LastMouseCoordinates.getX();
		float deltaY = y - LastMouseCoordinates.getY();

		// Ctrl button has priority.
		if (Modifiers & GLUT_ACTIVE_CTRL) {
			Camera::Zoom(deltaY * -0.01);
		}

		// Shift button has next priority.
		else if (Modifiers & GLUT_ACTIVE_SHIFT) {
			Camera::LocalTranslate(deltaX * 0.001, deltaY * -0.001);
		}

		// If invalid modifiers or no modifers were pressed...
		else {
			Camera::Pivot(deltaY * 0.005, deltaX * -0.005);
		}
	}
	LastMouseCoordinates = Vector2f(x, y);
}

void Input::PassiveMotion(int x, int y) {

}

void Input::Keyboard(unsigned char key, int mouseX, int mouseY) {
	switch (key) {

	// Clear the screen and make the program ready to create a new model.
	case 'c':
	case 'C':
		// TODO Implement this
		break;

	// Make the camera focus on the object.
	case 'f':
	case 'F':
		Camera::TransitionTo(Vector3f::Zero(), 5.0f, 15); // TODO use correct vector
		break;

	// Toggle the model to render between gold and plastic materials.
	case 'g':
	case 'G':
		Draw::ToggleMaterial();
		break;

	// Move the camera along a predefined path.
	case 'm':
	case 'M':
		Camera::PlayAnimation(Vector3f::Zero()); // TODO use correct vector
		break;

	// Move the camera to face the XY plane.
	case 'v':
	case 'V':
		Camera::TransitionTo(Vector3f(0.0f, 0.0f, 11.95f), Vector3f::Zero(), 15);
		break;

	default:
		break;
	}
}

void Input::SpecialKeyboard(int key, int mouseX, int mouseY) {
	
}

void Input::ModifiersTest() {
	cout << Modifiers << endl;
	if (Modifiers & GLUT_ACTIVE_SHIFT) {
		cout << "Shift pressed." << endl;
	}
	if (Modifiers & GLUT_ACTIVE_CTRL) {
		cout << "Ctrl pressed." << endl;
	}
	if (Modifiers & GLUT_ACTIVE_ALT) {
		cout << "Alt pressed." << endl;
	}
}