#include "ColorRGB.h"

vector<ColorRGB> ColorRGB::colors = {
	ColorRGB(255, 0, 0),
	ColorRGB(0, 255, 0),
	ColorRGB(0, 0, 255),
	ColorRGB(0, 255, 255),
	ColorRGB(255, 0, 255),
	ColorRGB(255, 255, 0)
};

ColorRGB ColorRGB::Random() {
	ColorRGB color = colors[rand() * colors.size() / RAND_MAX];
	return color;
}

ColorRGB::ColorRGB(): ColorRGB(0, 0, 0) {}

ColorRGB::ColorRGB(int r, int g, int b) {
	setR(r);
	setG(g);
	setB(b);
}

ColorRGB::~ColorRGB() {}

int ColorRGB::getR() {
	return r;
}

void ColorRGB::setR(int r) {
	ColorRGB::r = r < 0 ? 0 : r > 255 ? 255 : r;
}

int ColorRGB::getG() {
	return g;
}

void ColorRGB::setG(int g) {
	ColorRGB::g = g < 0 ? 0 : g > 255 ? 255 : g;
}

int ColorRGB::getB() {
	return b;
}

void ColorRGB::setB(int b) {
	ColorRGB::b = b < 0 ? 0 : b > 255 ? 255 : b;
}

float ColorRGB::getFloatR() {
	return r / 255.0f;
}

float ColorRGB::getFloatG() {
	return g / 255.0f;
}

float ColorRGB::getFloatB() {
	return b / 255.0f;
}