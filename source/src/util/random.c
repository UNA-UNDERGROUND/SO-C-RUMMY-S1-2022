#include <rummy/util/random.h>
#include <stddef.h>
#define _XOPEN_SOURCE 
#include <stdlib.h>
#include <time.h>

void reseed() {
	srand(time(NULL));
#ifdef _WIN32
	srand((long)time(NULL));
#else
	srand48((long)time(NULL));
#endif
}

float randomFloat() {
#ifdef _WIN32
	return (float)(rand()) / RAND_MAX;
#else
	return (float)(drand48());
#endif
}

int randomInt(int min, int max) {
	return (int)(randomFloat() * (max - min + 1)) + min;
}