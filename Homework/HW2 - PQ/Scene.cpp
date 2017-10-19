#include "Scene.h"
#include <ctime>
#include <cmath>

Scene Scene::Instance = Scene();

Scene::Scene() {
	srand((unsigned)time(0));

	// TODO Initialize scene here.
	roomDimensions = Vector3f(2, 2, 2);
}

Scene& Scene::GetInstance() {
	return Instance;
}

Vector3f& Scene::GetRoomDimensions() {
	return GetInstance().roomDimensions;
}