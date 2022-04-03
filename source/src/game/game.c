#include "rummy/game/player.h"
#include "rummy/render/render.h"
#include <assert.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <rummy/game/combination.h>
#include <rummy/game/deck.h>
#include <rummy/game/game.h>
#include <rummy/util/memory/vector.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// mutex sync flags
pthread_mutex_t players_mutex[4] = {
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};
int actual_player_id = -1;
int player_finished = 0;
int end_game = 0;
int game_started = 0;

game_state_t game_state;

void init_player(Player *player, int id) {
	assert(player != NULL);
	player->id = id;
	// init the player's hand
	player->hand = init_hand();
}
void clear_player(Player *player) {
	assert(player != NULL);
	player->id = -1;
	// clear the player's hand
	delete_hand(player->hand);
}
void init_game_state() {
	initDeck(&game_state.board.deck);
	shuffleDeck(&game_state.board.deck);
	new_vector(&game_state.board.combinations);
	// init players
	for (int i = 0; i < 4; i++) {
		init_player(&game_state.players[i], i);
	}
}
void clear_game_state() {
	// clear players
	for (int i = 0; i < 4; i++) {
		clear_player(&game_state.players[i]);
	}
	delete_vector(game_state.board.combinations, combination_deleter);
	clearDeck(&game_state.board.deck);
}

void game_logic() {
	int option = 0;
	clear_screen();
	printf("Do you want to end the game?\n");
	printf("1. Yes\n");
	printf("2. No\n");
	scanf("%d", &option);
	if (option == 1) {
		end_game = 1;
	}
}
void player_logic(int player_id) {
	clear_screen();
	printf("player : %d thread\n", player_id);
	sleep(1);
}

void *game_thread_main(void *ptr) {
	init_game_state();
	// lock the players mutex
	for (int i = 0; i < 4; i++) {
		pthread_mutex_lock(&players_mutex[i]);
	}
	player_finished = 0;
	game_started = 1;
	actual_player_id = 0;
	end_game = 0;

	while (end_game == 0) {
		game_logic();
		if (end_game == 1) {
			break;
		}
		// unlock the actual player mutex
		pthread_mutex_unlock(&players_mutex[actual_player_id]);
		// wait until the actual player finish his turn
		while (player_finished == 0) {
			sched_yield();
		}
		player_finished = 0;
		// lock the actual player mutex
		pthread_mutex_lock(&players_mutex[actual_player_id]);
		// get the next player
		actual_player_id = (actual_player_id + 1) % 4;
	}
	clear_game_state();
	// unlock the players mutex
	for (int i = 0; i < 4; i++) {
		pthread_mutex_unlock(&players_mutex[i]);
	}
	player_finished = 0;
	game_started = 0;
	return 0;
}
void *player_thread(void *player_id_ptr) {
	int player_id = *((int *)player_id_ptr);
	// wait until game is started
	while (game_started == 0) {
		sched_yield();
	}
	// player loop
	while (end_game == 0) {
		pthread_mutex_lock(&players_mutex[player_id]);
		if (end_game == 1) {
			pthread_mutex_unlock(&players_mutex[player_id]);
			break;
		}
		player_logic(player_id);
		player_finished = 1;
		pthread_mutex_unlock(&players_mutex[player_id]);
	}
	return 0;
}