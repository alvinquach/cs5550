#include "Input.h"
#include "Scene.h"

void Input::keyboard(unsigned char key, int mouseX, int mouseY) {

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

	}

}

void Input::specialKeyboard(int key, int mouseX, int mouseY) {

}
