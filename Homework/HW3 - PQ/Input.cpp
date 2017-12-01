// Alvin Quach, 300793745
// CS5550 F17 - HW3 PQ

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "Camera.h"
#include "Draw.h"
#include "Model.h"
#include "Utils.h"

#include "Input.h"

using std::cout;
using std::endl;

// Initialize variables
int Input::GridMode = 0;
bool Input::SampleMouseOnNextUpdate = false;
int Input::Modifiers = 0;
int Input::ActiveButton = -1;

/// <summary>Initial coordinates of the object on the screen.</summary>
Vector2f Input::InitialScreenCoordinates = Vector2f::Zero();

/// <summary>Initial coordinates of the mouse on the screen.</summary>
Vector2f Input::InitialMouseCoordinates = Vector2f::Zero();

/// <summary>Latest coordinates of the mouse in the world.</summary>
Vector3f Input::LastWorldCoordinates = Vector3f::Zero();

/// <summary>Latest coordinates of the mouse on the screen.</summary>
Vector2f Input::LastMouseCoordinates = Vector2f::Zero();

float* Input::InitialTransformation = Utils::Identity4x4();

float Input::ViewPlaneDistance = 0.0f;

void Input::Mouse(int button, int state, int x, int y) {
	float* m = Utils::test();
	cout << "Mouse Input: (" << button << ", " << state << ", " << x << ", " << y << ")" << endl;
	if (state == GLUT_DOWN) {
		if (ActiveButton < 0) {
			if (button == GLUT_MIDDLE_BUTTON) {
				Modifiers = glutGetModifiers();
				SampleMouseOnNextUpdate = true;
			}
			if (button == GLUT_LEFT_BUTTON) {
				return;
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
		if (button == GLUT_MIDDLE_BUTTON && ActiveButton == GLUT_MIDDLE_BUTTON) {
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
		ViewPlaneDistance = Camera::GetDistanceFrom(Model::GetMesh().getTranslation());
		LastWorldCoordinates = Camera::GetWorldCoordinatesOf(x, y, ViewPlaneDistance);
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
			GridMode = 0;
			Camera::Pivot(deltaY * 0.005, deltaX * -0.005);
		}
	}

	else if (ActiveButton == GLUT_RIGHT_BUTTON) {
		if (deltaX > 0 || deltaY > 0) {
			ActiveButton = 'g';
			Utils::CopyMatrix(Model::GetMesh().getTranslation().asArray(), InitialTransformation, 3);
			SampleMouseOnNextUpdate = true;
		}
	}

	else if (ActiveButton == 'g') {
		Vector3f worldCoord = Camera::GetWorldCoordinatesOf(x, y, ViewPlaneDistance);
		Model::GetMesh().translate(worldCoord - LastWorldCoordinates);
		LastWorldCoordinates = worldCoord;
	}

	else if (ActiveButton == 'r') {
		float ang1 = (Vector2f(x, y) - InitialScreenCoordinates).angle();
		float ang2 = (LastMouseCoordinates - InitialScreenCoordinates).angle();
		float* rot = Camera::GetRotationMatrixAboutLookDirection(ang2 - ang1);
		Model::GetMesh().rotate(rot);
		delete[] rot;
	}

	else if (ActiveButton == 's') {
		float initialDistance = (InitialMouseCoordinates - InitialScreenCoordinates).getMagnitude();
		float currentDistance = (Vector2f(x, y) - InitialScreenCoordinates).getMagnitude();
		Model::GetMesh().setScale(currentDistance / initialDistance * InitialTransformation[0]);
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
			Utils::CopyMatrix(Model::GetMesh().getTranslation().asArray(), InitialTransformation, 3);
			if (ActiveButton < 0) {
				SampleMouseOnNextUpdate = true;
			}
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

	// Reset object transformations
	case 'o':
	case 'O':
		Model::GetMesh().resetTransformations();
		break;

	// Enter rotation mode.
	case 'r':
	case 'R':
		if (ActiveButton < 0 || ActiveButton == 'g' || ActiveButton == 's') {
			ResetTransformMode();
			Utils::CopyMatrix(Model::GetMesh().getRotation(), InitialTransformation, 16);
			InitialScreenCoordinates = Utils::GetScreenCoordnates(Model::GetMesh().getTranslation());
			if (ActiveButton < 0) {
				SampleMouseOnNextUpdate = true;
			}
			ActiveButton = 'r';
		}
		break;

	// Enter scale mode.
	case 's':
	case 'S':
		if (ActiveButton < 0 || ActiveButton == 'g' || ActiveButton == 'r') {
			ResetTransformMode();
			InitialTransformation[0] = Model::GetMesh().getScale();
			InitialScreenCoordinates = Utils::GetScreenCoordnates(Model::GetMesh().getTranslation());
			if (ActiveButton < 0) {
				SampleMouseOnNextUpdate = true;
			}
			ActiveButton = 's';
		}
		break;

	// Move the camera to face the YZ plane.
	case 'x':
	case 'X':
		Camera::TransitionTo(Vector3f(11.95f, 0.0f, 0.0f), Vector3f::Zero(), 15);
		GridMode = 1;
		break;

	// Move the camera to face the XZ plane.
	case 'y':
	case 'Y':
		Camera::TransitionTo(Vector3f(0.0f, 11.95f, 0.0f), Vector3f::Zero(), 15);
		GridMode = 0;
		break;

	// Move the camera to face the XY plane.
	case 'z':
	case 'Z':
		Camera::TransitionTo(Vector3f(0.0f, 0.0f, 11.95f), Vector3f::Zero(), 15);
		GridMode = 2;
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
	cout << "RESET" << endl;
	switch (ActiveButton) {
	case 'g':
		Model::GetMesh().setTranslation(Vector3f(InitialTransformation[0], InitialTransformation[1], InitialTransformation[2]));
		break;
	case 'r':
		Model::GetMesh().setRotation(InitialTransformation);
		break;
	case 's':
		Model::GetMesh().setScale(InitialTransformation[0]);
		break;
	}
	InitialScreenCoordinates = Vector2f::Zero();
	Utils::SetIdentity4x4(InitialTransformation);
}

void Input::CompleteTransformMode() {
	InitialScreenCoordinates = Vector2f::Zero();
	Utils::SetIdentity4x4(InitialTransformation);
}