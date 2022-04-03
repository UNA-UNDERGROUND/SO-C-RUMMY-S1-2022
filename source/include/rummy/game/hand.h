#pragma once
#include <rummy/game/card.h>
#include <rummy/util/memory/vector.h>

// Hand C struct
typedef struct {
	int id;
	Vector *cards;
} Hand;

/**
 * @brief Create a Hand object
 *
 * @param id the id of the hand
 * @return Hand* the hand created
 */
Hand *init_hand(int id);

/**
 * @brief add a card to the hand
 *
 * @param hand the hand to add the card to
 * @param card the card to add
 */
void add_card(Hand *hand, Card *card);

/**
 * @brief remove a card from the hand
 *
 * @param hand the hand to remove the card from
 * @param card the card to remove
 */
void remove_card(Hand *hand, Card *card);

/**
 * @brief delete a Hand object
 *
 * @param hand the hand to delete
 */
void delete_hand(Hand *hand);