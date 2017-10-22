// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#include "Input.h"
#include "Scene.h"

/*
void Input::Mouse(int button, int state, int x, int y) {

}

void Input::Motion(int x, int y) {

}
*/

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

	}
}

void Input::SpecialKeyboard(int key, int mouseX, int mouseY) {

}
