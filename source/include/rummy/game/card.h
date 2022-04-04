#pragma once

// RGBY
typedef enum {
	JOKER = -1,
	RED = 0,
	GREEN = 1,
	BLUE = 2,
	YELLOW = 3,
} card_color_t;

// -1 is the joker or wildcard
typedef struct {
	int unique_id;
	card_color_t color;
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
Card *createCard(card_color_t color, int value, int unique_id);

/**
 * @brief card deleter
 *
 * @param card the card to delete
 */
void card_deleter(void *card);