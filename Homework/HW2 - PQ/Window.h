// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#pragma once
#include <gl/Gl.h>
#include "glut.h"

class Window {

public:

	/// <summary>Width of screen window in pixels.</summary>
	static const int ScreenWidth;

	/// <summary>Height of screen window in pixels.</summary>
	static const int ScreenHeight;

	/// <summary>Initial screen position x.</summary>
	static const int ScreenPositionX;

	/// <summary>Initial screen position y.</summary>
	static const int ScreenPositionY;

	/// <summary>The width of the world.</summary>
	static const float WorldWidth;

	/// <summary>The height of the world.</summary>
	static const float WorldHeight;

	/// <summary>Distance of the near-Z clipping plane from the camera.</summary>
	static const float NearZClipPlane;

	/// <summary>Distance of the far-Z clipping plane from the camera.</summary>
	static const float FarZClipPlane;

	/// <summary>How many frames are drawn per second.</summary>
	static const float FrameRate;

	static void SetWindow();

};
