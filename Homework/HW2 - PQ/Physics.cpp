#include "Physics.h"

const int Physics::UpdatesPerFrame = 10;

// This is calculated from UpdateRate.
const double Physics::DeltaTime = 1.0 / (UpdatesPerFrame * Window::FrameRate);

void Physics::Update() {
	Scene::GetRobot().updateTimer(DeltaTime);
}