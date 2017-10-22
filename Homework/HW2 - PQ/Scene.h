#pragma once
#include <Windows.h>
#include "glut.h"
#include "Vector3f.h"
#include "Camera.h"
#include "Robot.h"

class Scene {

public:

	static Scene& GetInstance();
	static void Reset();
	static Vector3f& GetRoomDimensions();

	/// <summary>Toggles the rendering mode and returns the new rendering mode.</summary>
	static GLenum ToggleRenderMode();

	/// <summary>Returns the current rendering mode.</summary>
	static GLenum GetRenderMode();

	static Camera& GetCamera();

	static Robot& GetRobot();

private:

	Scene();

	static Scene Instance;

	/// <summary>Dimensions of the room.</summary>
	Vector3f roomDimensions;

	/// <summary>Rendering mode (0 = wire, 1 = solid).</summary>
	GLenum renderMode;

	Camera camera;

	Robot robot;
	
};