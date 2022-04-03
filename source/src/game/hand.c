#include <rummy/game/card.h>
#include <rummy/game/hand.h>
#include <stdlib.h>

Hand *init_hand(int id) {
	Hand *hand = malloc(sizeof(Hand));
	hand->id = id;
	hand->cards = new_vector();
	return hand;
}

void add_card(Hand *hand, Card *card) { vector_push_back(hand->cards, card); }

void remove_card(Hand *hand, Card *card) {
	// find the index of the card
	int index = -1;
	for (int i = 0; i < hand->cards->size; i++) {
		Card *c = (Card *)hand->cards->data;
		if (c->color == card->color && c->value == card->value) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		vector_remove(hand->cards, index);
	}
}

void delete_hand(Hand *hand) {
	// the vector contains a view of the cards
	delete_vector(hand->cards, view_deleter);
	free(hand);
}