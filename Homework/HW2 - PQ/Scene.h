#pragma once
#include "Vector3f.h"

class Scene {

public:

	static Scene& GetInstance();
	static Vector3f& GetRoomDimensions();

private:

	Scene();

	/// <summary>Singleton instance of the scene.</summary>
	static Scene Instance;

	/// <summary>Dimensions of the room.</summary>
	Vector3f roomDimensions;
	
};