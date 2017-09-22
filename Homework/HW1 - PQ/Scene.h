#pragma once
#include <vector>
#include "Ball.h"

using namespace std;

struct Color {
	ColorRGB color;
	int count;
};

class Scene {
public:
	static const int MaxBallCount;
	static Scene& GetInstance();
	static void Reset();
	static vector<Ball>& GetBalls();
	static Ball& AddBall();
	static void RemoveLastBall();

private:
	static Scene Instance;
	Scene();
	vector<Ball> balls;
	Ball& addBall();
};



