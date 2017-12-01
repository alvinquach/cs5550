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