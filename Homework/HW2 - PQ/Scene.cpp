#include "Scene.h"
#include <ctime>
#include <cmath>

Scene Scene::Instance = Scene();

Scene::Scene() {
	srand((unsigned)time(0));
	// TODO Initialize scene here.
}