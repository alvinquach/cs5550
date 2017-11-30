// Alvin Quach, 300793745
// CS5550 F17 - HW3 PQ

#include <iostream>

#include "Camera.h"
#include "Draw.h"
#include "Model.h"
#include "Utils.h"

#include "Input.h"

using std::cout;
using std::endl;

// Initialize variables
bool Input::SampleMouseOnNextUpdate = false;
int Input::Modifiers = 0;
int Input::ActiveButton = -1;
Vector2f Input::InitialScreenCoordinates = Vector2f::Zero();
Vector2f Input::InitialMouseCoordinates = Vector2f::Zero();
Vector2f Input::LastMouseCoordinates = Vector2f::Zero();
Vector3f Input::InitialTransformation = Vector3f::Zero();

void Input::Mouse(int button, int state, int x, int y) {
	float* m = Utils::test();
	cout << "Mouse Input: (" << button << ", " << state << ", " << x << ", " << y << ")" << endl;
	if (state == GLUT_DOWN) {
		if (ActiveButton < 0) {
			if (button == GLUT_MIDDLE_BUTTON) {
				Modifiers = glutGetModifiers();
				SampleMouseOnNextUpdate = true;
			}
			ActiveButton = button; // Set active button.
			
			Camera::Interrupt();
		}
		else if (ActiveButton != GLUT_MIDDLE_BUTTON) {
			if (button == GLUT_RIGHT_BUTTON) {
				ResetTransformMode();
				ActiveButton = -1;
			}
			else if (button == GLUT_LEFT_BUTTON) {
				CompleteTransformMode();
				ActiveButton = -1;
			}
		}
	}
	else if (state == GLUT_UP) {
		if (button == GLUT_MIDDLE_BUTTON) {
			Modifiers = 0;
			ActiveButton = -1; // Reset active button.
		}
		else if (button == GLUT_RIGHT_BUTTON && ActiveButton == GLUT_RIGHT_BUTTON) {
			ActiveButton = -1;
		}
	}
}

void Input::Motion(int x, int y) {

	if (SampleMouseOnNextUpdate) {
		LastMouseCoordinates = InitialMouseCoordinates = Vector2f(x, y);
		SampleMouseOnNextUpdate = false;
	}

	if (ActiveButton < 0) {
		return;
	}

	float deltaX = x - LastMouseCoordinates.getX();
	float deltaY = y - LastMouseCoordinates.getY();

	if (ActiveButton == GLUT_MIDDLE_BUTTON) {

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

	else if (ActiveButton == GLUT_RIGHT_BUTTON) {
		if (deltaX > 0 || deltaY > 0) {
			ActiveButton = 'g';
			InitialTransformation = Model::GetMesh().getTranslation();
			SampleMouseOnNextUpdate = true;
		}
	}

	else if (ActiveButton == 'g') {
		Vector2f& asdf = Utils::GetScreenCoordnates(Vector3f::Zero());
		//cout << asdf.getX() << " " << asdf.getY() << endl;
		Model::GetMesh().translate(Vector3f(deltaX / 100.0, 0, deltaY / 100.0));
	}

	else if (ActiveButton == 'r') {
		Vector2f& asdf = Utils::GetScreenCoordnates(Vector3f::Zero());
		//cout << asdf.getX() << " " << asdf.getY() << endl;
		Model::GetMesh().rotate(Vector3f(deltaX / 10.0, 0, deltaY / 10.0));
	}

	else if (ActiveButton == 's') {
		cout << InitialMouseCoordinates.getX() << " " << InitialMouseCoordinates.getY() << endl;
		cout << x << " " << y << endl;
		cout << InitialScreenCoordinates.getX() << " " << InitialScreenCoordinates.getY() << endl;
		cout << endl;
		float initialDistance = (InitialMouseCoordinates - InitialScreenCoordinates).getMagnitude();
		float currentDistance = (Vector2f(x, y) - InitialScreenCoordinates).getMagnitude();
		Model::GetMesh().setScale(currentDistance / initialDistance * InitialTransformation.getX());
	}

	LastMouseCoordinates = Vector2f(x, y);
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
		Camera::TransitionTo(Model::GetMesh().getTranslation(), 5.0f, 15); // TODO get object size
		break;

	// Enter translate mode.
	case 'g':
	case 'G':
		if (ActiveButton < 0 || ActiveButton == 'r' || ActiveButton == 's') {
			ResetTransformMode();
			InitialTransformation = Model::GetMesh().getTranslation();
			SampleMouseOnNextUpdate = true;
			ActiveButton = 'g';
		}
		break;

	// Toggle the model to render between gold and plastic materials.
	case 'h':
	case 'H':
		Draw::ToggleMaterial();
		break;

	// Move the camera along a predefined path.
	case 'm':
	case 'M':
		Camera::PlayAnimation(Model::GetMesh().getTranslation());
		break;

	// Enter rotation mode.
	case 'r':
	case 'R':
		if (ActiveButton < 0 || ActiveButton == 'g' || ActiveButton == 's') {
			ResetTransformMode();
			InitialTransformation = Model::GetMesh().getRotation();
			SampleMouseOnNextUpdate = true;
			ActiveButton = 'r';
		}
		break;

	// Enter scale mode.
	case 's':
	case 'S':
		if (ActiveButton < 0 || ActiveButton == 'g' || ActiveButton == 'r') {
			ResetTransformMode();
			InitialTransformation.setX(Model::GetMesh().getScale());
			InitialScreenCoordinates = Utils::GetScreenCoordnates(Model::GetMesh().getTranslation());
			SampleMouseOnNextUpdate = true;
			ActiveButton = 's';
		}
		break;

	// Move the camera to face the YZ plane.
	case 'x':
	case 'X':
		Camera::TransitionTo(Vector3f(11.95f, 0.0f, 0.0f), Vector3f::Zero(), 15);
		break;

	// Move the camera to face the XZ plane.
	case 'y':
	case 'Y':
		Camera::TransitionTo(Vector3f(0.0f, 11.95f, 0.0f), Vector3f::Zero(), 15);
		break;

	// Move the camera to face the XY plane.
	case 'z':
	case 'Z':
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

void Input::ResetTransformMode() {
	switch (ActiveButton) {
	case 'g':
		Model::GetMesh().setTranslation(InitialTransformation);
		break;
	case 'r':
		Model::GetMesh().setRotation(InitialTransformation);
		break;
	case 's':
		Model::GetMesh().setScale(InitialTransformation.getX());
		break;
	}
	InitialScreenCoordinates = Vector2f::Zero();
	InitialTransformation = Vector3f::Zero();
}

void Input::CompleteTransformMode() {
	InitialScreenCoordinates = Vector2f::Zero();
	InitialTransformation = Vector3f::Zero();
}