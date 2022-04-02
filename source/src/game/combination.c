#include <rummy/game/combination.h>
#include <stdlib.h>

void combination_deleter(void *ptr) {
	combination_t *combination = (combination_t *)ptr;
	// the combination has a view of the elements of the combination
	// just set the pointer to NULL
	combination->num_cards = 0;
	for (int i = 0; i < COMBINATION_MAX_CARDS; i++) {
		combination->cards[i] = NULL;
	}
	free(combination);
}