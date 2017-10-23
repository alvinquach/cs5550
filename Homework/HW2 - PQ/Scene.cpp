#include "Scene.h"
#include <ctime>
#include <cmath>

/// <summary>Singleton instance of the scene.</summary>
Scene Scene::Instance = Scene();

Scene::Scene() {
	srand((unsigned)time(0));

	// TODO Initialize scene here.
	camera = Camera();
	roomDimensions = Vector3f(10, 10, 10);
	renderMode = GLU_FILL;
	showAxes = true;
	robotDisabled = false;
}

GLenum Scene::ToggleRenderMode() {
	if (Instance.renderMode == GLU_FILL) {
		return Instance.renderMode = GLU_LINE;
	}
	else {
		return Instance.renderMode = GLU_FILL;
	}
}

GLenum Scene::GetRenderMode() {
	return GetInstance().renderMode;
}

Camera& Scene::GetCamera() {
	return GetInstance().camera;
}

Robot& Scene::GetRobot() {
	return GetInstance().robot;
}

bool Scene::GetShowAxes() {
	return GetInstance().showAxes;
}

void Scene::ToggleShowAxes() {
	GetInstance().showAxes = !GetInstance().showAxes;
}

void Scene::DisableRobot() {
	GetInstance().robotDisabled = true;
}

void Scene::EnableRobot() {
	GetInstance().robotDisabled = false;
}

bool Scene::IsRobotDisabled() {
	return GetInstance().robotDisabled;
}

Scene& Scene::GetInstance() {
	return Instance;
}

void Scene::Reset() {
	Instance = Scene();
}

Vector3f& Scene::GetRoomDimensions() {
	return GetInstance().roomDimensions;
}

