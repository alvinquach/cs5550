#include "Scene.h"
#include <iostream>

Scene Scene::Instance = Scene();

Scene& Scene::GetInstance() {
	return Instance;
}

void Scene::Reset() {
	Instance = Scene();
}

Scene::Scene()
{
	std::cout << "RESET!" << std::endl;
	Ball& ball = addBall(6.9);
	ball.setVelocity(Vector2f(13, 37));
	addBall(6.9).setVelocity(Vector2f(-4, -20));
}

vector<Ball>& Scene::GetBalls() {
	return GetInstance().balls;
}

Ball& Scene::AddBall() {
	return AddBall(6.9);
}

Ball& Scene::AddBall(float radius) {
	return Instance.addBall(radius);
}

Ball& Scene::addBall(float radius) {
	Ball ball = Ball();
	ball.setColor(ColorRGB::Random());
	ball.setRadius(radius);
	balls.push_back(ball);
	return balls.back();
}


