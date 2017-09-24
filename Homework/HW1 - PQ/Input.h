#pragma once
#include "Vector2f.h"

class Input {

public:
	static void Mouse(int button, int state, int x, int y);
	static void Motion(int x, int y);
	static void Keyboard(unsigned char key, int mouseX, int mouseY);
	static void SpecialKeyboard(int key, int mouseX, int mouseY);
private:
	static const float BallRadiusDeltaAmount;
	static const float BallSpeedDeltaAmount;
	static Vector2f& ConvertScreenToWorld(Vector2f& screenCoordinates);
};

