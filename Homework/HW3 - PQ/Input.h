#pragma once
#include "Vector2f.h"
#include "Vector3f.h"

class Input {

public:
	static void Mouse(int button, int state, int x, int y);
	static void Motion(int x, int y);
	static void Keyboard(unsigned char key, int mouseX, int mouseY);
	static void SpecialKeyboard(int key, int mouseX, int mouseY);
	static void ModifiersTest();

private:
	static bool SampleMouseOnNextUpdate;
	static int Modifiers;
	static int ActiveButton;
	static Vector2f InitialScreenCoordinates;
	static Vector2f InitialMouseCoordinates;
	static Vector3f LastWorldCoordinates;
	static Vector2f LastMouseCoordinates;
	static Vector3f InitialTransformation;
	static float ViewPlaneDistance;
	static void ResetTransformMode();
	static void CompleteTransformMode();
};