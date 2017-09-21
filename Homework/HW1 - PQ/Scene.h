#pragma once
#include <vector>
#include "Ball.h"

using namespace std;

class Scene {
public:
	vector<Ball> balls;
	Scene();
	~Scene();
};

