#pragma once
#include <vector>
#include "Ball.h"

using namespace std;

class Scene {
public:
	static Scene& GetInstance();
	static void Reset();
	static vector<Ball>& GetBalls();
	static Ball& AddBall();
	static Ball& AddBall(float radius);

private:
	static Scene Instance;
	Scene();
	vector<Ball> balls;
	Ball& addBall();
	Ball& addBall(float radius);
};

