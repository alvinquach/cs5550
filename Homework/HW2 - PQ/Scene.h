// Alvin Quach, 300793745
// CS5550 F17 - HW2 PQ

#pragma once
#include <vector>
#include <Windows.h>
#include "glut.h"
#include "Vector3f.h"
#include "Camera.h"
#include "Robot.h"
#include "Ball.h"

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

	static vector<Ball>& GetBalls();

	static Ball& LaunchBall(Vector3f& position, Vector3f& velocity);

	static bool GetShowAxes();

	static void ToggleShowAxes();

private:

	Scene();

	static Scene Instance;

	/// <summary>Dimensions of the room.</summary>
	Vector3f roomDimensions;

	/// <summary>Rendering mode (0 = wire, 1 = solid).</summary>
	GLenum renderMode;

	Camera camera;

	Robot robot;

	vector<Ball> balls;

	bool showAxes;

};