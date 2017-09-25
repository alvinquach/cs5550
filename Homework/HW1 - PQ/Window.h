// Alvin Quach, 300793745
// CS5550 F17 - HW1 PQ

#pragma once
#include "ColorRGB.h"

//Global Variables
const int screenWidth = 960;	   // width of screen window in pixels
const int screenHeight = 540;	   // height of screen window in pixels

/// <summary>Initial screen position x.</summary>
const int screenPositionX = 50;

/// <summary>Initial screen position y.</summary>
const int screenPositionY = 50;

/// <summary>The width of the world.</summary>
const float worldWidth = 100.0;

/// <summary>The height of the world.</summary>
const float worldHeight = worldWidth * screenHeight / screenWidth;

/// <summary>How many frames are drawn per second.</summary>
const float frameRate = 60.0;
