// Alvin Quach, 300793745
// CS5550 F17 - HW1 PQ

#include "Scene.h"
#include <ctime>

const int Scene::MaxBallCount = 5;

Scene Scene::Instance = Scene();

Scene& Scene::GetInstance() {
	return Instance;
}

void Scene::Reset() {
	Instance = Scene();
}

vector<Ball>& Scene::GetBalls() {
	return GetInstance().balls;
}

Ball& Scene::AddBall() {
	return Instance.addBall();
}

void Scene::RemoveLastBall() {
	Instance.balls.pop_back();
	if (Instance.selectedBallIndex >= Instance.balls.size()) {
		Instance.selectedBallIndex = -1;
	}
}

Ball *Scene::GetSelectedBall() {
	if (Instance.selectedBallIndex < 0) {
		return nullptr;
	}
	return &Instance.balls[Instance.selectedBallIndex];
}

void Scene::SelectBall(int index) {
	if (index < (int)Instance.balls.size()) {
		Instance.selectedBallIndex = index;
	}
}

int Scene::GetLockedBallIndex() {
	return Instance.lockedBallIndex;
}

Ball *Scene::GetLockedBall() {
	if (Instance.lockedBallIndex < 0) {
		return nullptr;
	}
	return &Instance.balls[Instance.lockedBallIndex];
}

void Scene::LockBall(int index) {
	if (index < (int)Instance.balls.size()) {
		Instance.lockedBallIndex = index;
	}
}

Scene::Scene() {
	srand((unsigned)time(0));
	addBall();
	addBall();
	selectedBallIndex = -1;
	lockedBallIndex = -1;
}

Ball& Scene::addBall() {
	balls.push_back(Ball::Random());
	return balls.back();
}


