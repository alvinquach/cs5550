#include "Scene.h"
#include <iostream>

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
}

Scene::Scene() {
	addBall();
	addBall();
}

Ball& Scene::addBall() {
	balls.push_back(Ball::Random());
	return balls.back();
}


