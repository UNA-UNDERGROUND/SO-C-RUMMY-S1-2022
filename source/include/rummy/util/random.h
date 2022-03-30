#pragma once
// utilities for randomization

/**
 * @brief reseeds the random generator
 *
 */
void reseed();

/**
 * @brief returns a random float between 0 and 1
 *
 */
float randomFloat();

/**
 * @brief returns a random number between min and max(inclusive)
 *
 * @param min the minimum number
 * @param max the maximum number
 * @return int the random number
 */
int randomInt(int min, int max);