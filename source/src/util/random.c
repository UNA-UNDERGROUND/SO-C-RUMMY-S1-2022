#include <rummy/util/random.h>
#include <stddef.h>
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int seeded = 0;

void reseed() {
	srand(time(NULL));
	srand48((long)time(NULL));
}

float randomFloat() {
	if (!seeded) {
		reseed();
		seeded = 1;
	}
	return (float)(drand48());
}

int randomInt(int min, int max) {
	if (!seeded) {
		reseed();
		seeded = 1;
	}
	return (min + randomFloat() * (max - min));
}