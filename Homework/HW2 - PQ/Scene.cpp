#include "Scene.h"
#include <ctime>
#include <cmath>

/// <summary>Singleton instance of the scene.</summary>
Scene Scene::Instance = Scene();

Scene::Scene() {
	srand((unsigned)time(0));

	// TODO Initialize scene here.
	camera = Camera();
	roomDimensions = Vector3f(4, 4, 4);
	renderMode = GLU_FILL;
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

Scene& Scene::GetInstance() {
	return Instance;
}

void Scene::Reset() {
	Instance = Scene();
}

Vector3f& Scene::GetRoomDimensions() {
	return GetInstance().roomDimensions;
}

