#include "Point2f.h"

Point2f::Point2f() {}

Point2f::Point2f(float x, float y) {
	Point2f::x = x;
	Point2f::y = y;
}

float Point2f::getX() {
	return x;
}

void Point2f::setX(float x) {
	Point2f::x = x;
}

float Point2f::getY() {
	return y;
}

void Point2f::setY(float y) {
	Point2f::y = y;
}

