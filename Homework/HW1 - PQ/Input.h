#pragma once

class Input
{
public:
	static void keyboard(unsigned char key, int mouseX, int mouseY);
	static void specialKeyboard(int key, int mouseX, int mouseY);
private:
	static float BallRadiusDeltaAmount;
};

