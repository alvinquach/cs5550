#pragma once

class Utils {
public:
	static float* Multiply4x4x4x1(float* a, float* b);
	static float* Multiply4x4x4x4(float* a, float* b);
	static void Print4x4(float* matrix);
	static void Print4x1(float* matrix);
	static float Clamp(float value, float min, float max);
	static float* test();
};