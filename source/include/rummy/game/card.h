#pragma once

// -1 is the joker or wildcard

typedef struct {
	int color;
	int value;
} Card;

/**
 * @brief Create a Card object
 *
 * @note if the color or value are invalid, the card will be a joker
 *
 * @param color the color of the card
 * @param value the value of the card
 * @return Card* the card created
 */
Card *createCard(int color, int value);

/**
 * @brief card deleter
 *
 * @param card the card to delete
 */
void card_deleter(void *card);