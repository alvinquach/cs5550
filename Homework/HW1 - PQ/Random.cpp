#include <cstdlib> 
#include "Random.h"

int Random::RandomInt(int max) {
	return RandomInt(0, max);
}

int Random::RandomInt(int min, int max) {
	return rand() * (max - min) / RAND_MAX + min;
}

float Random::RandomFloat(float max) {
	return RandomFloat(0, max);
}

float Random::RandomFloat(float min, float max) {
	return rand() * (max - min) / RAND_MAX + min;
}