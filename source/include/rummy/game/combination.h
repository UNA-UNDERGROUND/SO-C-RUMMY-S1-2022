#pragma once
#include <rummy/game/card.h>

#define COMBINATION_MAX_CARDS 4

typedef struct{
    int num_cards;
    Card *cards[COMBINATION_MAX_CARDS];
} combination_t;

void init_combination(combination_t *combination);

/**
 * @brief Function deleter for a list of pointers in a array, useful for objects
 * that need custom deallocation
 *
 */
void combination_deleter(void *ptr);