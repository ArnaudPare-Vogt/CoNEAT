#include "Function.h"

float sum(float n, float total) {
 return total + n;
}

float sigmoid(float x) {
	return 1.0f / (1.0f + std::exp(-x));
}

float fast_sigmoid(float x) {
	return 0.5 * (x / (1.0f + std::abs(x))) + 0.5;
}