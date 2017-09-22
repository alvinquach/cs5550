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
	static Ball *GetSelectedBall();
	static void SelectBall(int index);
private:
	static Scene Instance;
	Scene();
	vector<Ball> balls;
	int selectedBallIndex;
	Ball& addBall();
};



