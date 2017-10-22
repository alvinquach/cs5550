// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#include "Input.h"
#include "Scene.h"

const float Input::InputDelay = 100.0;

void Input::Keyboard(unsigned char key, int mouseX, int mouseY) {

	switch (key) {

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
		Scene::GetRobot().moveForward();

	case GLUT_KEY_DOWN:
		Scene::GetRobot().moveBackward();

	default:
		break;
	}

}
