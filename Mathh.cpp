#include "Mathh.h"
int pow(int a, int exp) {
	int result = a;
	if (exp == 0) {
		result /= result;
		return result;
	}
	else if (exp == 1) {
		return a;
	}
	else {
		for (int i = 2; i <= exp; i++) {
			result *= a;
		}
		return result;
	}
}