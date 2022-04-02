#pragma once
#include <rummy/util/memory/vector.h>
#include <rummy/game/card.h>
#include <rummy/game/deck.h>


typedef struct {
	Deck deck;
    Vector *combinations;
} Board;