#include "Input.h"
#include "Scene.h"

void Input::keyboard(unsigned char key, int mouseX, int mouseY) {

	switch (key) {

	case 'a':
		break;

	case 'n':
		Scene::Reset();
		break;

	}

}

void Input::specialKeyboard(int key, int mouseX, int mouseY) {

}
