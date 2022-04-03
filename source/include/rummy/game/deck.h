#pragma once
#include <rummy/game/card.h>

// se usan 2 juegos de bajaras, en otras palabras 104 naipes + 4 comodines
// 13 * 4 + 2 = 
#define SIZE_PER_DECK 54
#define DECK_MAX_SIZE 108

typedef struct {
	// up to 104 cards
	Card **cards;
	int size;
} Deck;

/**
 * @brief push a card to the deck, if the deck is full. the program will exit
 * with an assertion error
 *
 * @param deck the deck to push the card, if null do nothing
 * @param card the card to push, if null do nothing
 */
void pushCard(Deck *deck, Card *card);

/**
 * @brief pop a card from the deck
 *
 * @param deck the deck to pop from
 * @return Card* the card popped or NULL if the deck is empty
 */
Card *popCard(Deck *deck);

/**
 * @brief fill a deck with cards
 *
 * @note the card array must be null
 *
 * @param deck the deck to fill, if null do nothing
 */
void initDeck(Deck *deck);

/**
 * @brief shuffle the deck
 *
 * @param deck the deck to shuffle, if null do nothing
 */
void shuffleDeck(Deck *deck);

/**
 * @brief clear the deck and free the memory
 *
 * @param deck the deck to clear, if null do nothing
 */
void clearDeck(Deck *deck);