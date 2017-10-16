// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#pragma once

using namespace std;

class Input {

public:
	/*static void Mouse(int button, int state, int x, int y);
	static void Motion(int x, int y);*/
	static void Keyboard(unsigned char key, int mouseX, int mouseY);
	static void SpecialKeyboard(int key, int mouseX, int mouseY);
};

