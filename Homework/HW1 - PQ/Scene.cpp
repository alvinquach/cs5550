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
	addBall().setVelocity(Vector2f(13, 37));
	addBall().setVelocity(Vector2f(-4, -20));
}

vector<Ball>& Scene::GetBalls() {
	return GetInstance().balls;
}

Ball& Scene::AddBall() {
	return Instance.addBall();
}

Ball& Scene::AddBall(float radius) {
	return Instance.addBall(radius);
}

Ball& Scene::addBall() {
	return addBall(Ball::DefaultRadius);
}

Ball& Scene::addBall(float radius) {
	Ball ball = Ball(radius);
	ball.setColor(ColorRGB::Random());
	balls.push_back(ball);
	return balls.back();
}


