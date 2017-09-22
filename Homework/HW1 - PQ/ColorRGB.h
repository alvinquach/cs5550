#pragma once
#include <vector>

using namespace std;

class ColorRGB {
public:
	ColorRGB();
	ColorRGB(int r, int g, int b);
	~ColorRGB();
	int getR();
	void setR(int r);
	int getG();
	void setG(int g);
	int getB();
	void setB(int b);
	float getFloatR();
	float getFloatG();
	float getFloatB();
private:
	int r;
	int g;
	int b;
};

