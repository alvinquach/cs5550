#include "Scene.h"

Scene::Scene()
{
	Ball ball = Ball();
	ball.setColor(ColorRGB(0, 64, 255));
	ball.setVelocity(Vector2f(13, 37));
	ball.setRadius(6.9);
	balls.push_back(ball);

	ball = Ball();
	ball.setColor(ColorRGB(255, 0, 0));
	ball.setVelocity(Vector2f(-4, -20));
	ball.setRadius(6.9);
	balls.push_back(ball);
}


Scene::~Scene()
{
}
