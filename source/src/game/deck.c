#include "rummy/game/card.h"
#include <assert.h>
#include <rummy/game/deck.h>
#include <rummy/util/memory/allocator.h>
#include <rummy/util/random.h>
#include <stddef.h>

void pushCard(Deck *deck, Card *card) {
	if (deck == NULL || card == NULL) {
		return;
	}
	assert(deck->size < DECK_MAX_SIZE);
	deck->cards[deck->size++] = card;
}

Card *popCard(Deck *deck) {
	if (deck->size == 0) {
		return NULL;
	}
	Card *card = deck->cards[deck->size--];
	return card;
}

void initDeck(Deck *deck) {
	if (deck == NULL || deck->cards != NULL) {
		return;
	}
	deck->cards = (Card **)alloc_array(DECK_MAX_SIZE);
	// initialize the deck from 2 decks
	// the decks have card values from 0 to 13 in 4 colors + 2 jokers
	// the jokers are represented by the value -1
	for (int deck_n = 0; deck_n < 2; deck_n++) {
		for (int i = 0; i < DECK_MAX_SIZE; i++) {
			pushCard(deck, createCard(i / 13, i % 13));
		}
		// put 2 jokers at the end of the deck
		pushCard(deck, createCard(-1, -1));
		pushCard(deck, createCard(-1, -1));
	}
}

void shuffleDeck(Deck *deck) {
	if (deck == NULL || deck->cards == NULL) {
		return;
	}
	// shuffle the deck
	for (int i = 0; i < DECK_MAX_SIZE; i++) {
		int j = randomInt(0, DECK_MAX_SIZE - 1);
		Card *temp = deck->cards[i];
		deck->cards[i] = deck->cards[j];
		deck->cards[j] = temp;
	}
}

void clearDeck(Deck *deck) {
	if (deck == NULL || deck->cards == NULL) {
		return;
	}
	free_array((void **)deck->cards, DECK_MAX_SIZE, card_deleter);
}