// Alvin Quach, 300793745
// CS5550 F17 - HW3 PQ

#pragma once
#include <string>

using std::string;

class Window {

public:

	/// <summary>Window title</summary>
	static const string WindowName;

	/// <summary>Width of screen window in pixels.</summary>
	static const float ScreenWidth;

	/// <summary>Height of screen window in pixels.</summary>
	static const float ScreenHeight;

	/// <summary>Initial screen position x.</summary>
	static const int ScreenPositionX;

	/// <summary>Initial screen position y.</summary>
	static const int ScreenPositionY;

	/// <summary>How many frames are drawn per second.</summary>
	static const float FrameRate;

	static void SetWindow();

};