#include <rummy/game/card.h>
#include <stdlib.h>

Card *createCard(int color, int value) {
	Card *card = (Card *)malloc(sizeof(Card));
	card->color = color;
	card->value = value;
	if (color < 0 || color > 3 || value < 0 || value > 13) {
		card->color = -1;
		card->value = -1;
	}
	return card;
}

void card_deleter(void *card) { free(card); }