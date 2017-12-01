// Alvin Quach, 300793745
// CS5550 F17 - HW3 PQ

#pragma once
#include <vector>

#include "Vector3f.h"

using std::vector;

class Spline {
public:
	Spline();
	~Spline();
	vector<Vector3f>& getPoints();
private:
	vector<Vector3f> points;
};