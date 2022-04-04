#include <assert.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <rummy/game/card.h>
#include <rummy/game/combination.h>
#include <rummy/game/deck.h>
#include <rummy/game/game.h>
#include <rummy/game/hand.h>
#include <rummy/game/player.h>
#include <rummy/render/render.h>
#include <rummy/util/memory/vector.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

void render_player(Player *player);
void render_board_combinations();
void render_combination(combination_t *combination);

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
	// give the player 14 cards
	for (int i = 0; i < 14; i++) {
		add_card(player->hand, popCard(&game_state.board.deck));
	}
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
	game_state.board.combinations = new_vector();
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
	// int option = 0;
	// clear_screen();
	// printf("Do you want to end the game?\n");
	// printf("1. Yes\n");
	// printf("2. No\n");
	// scanf("%d", &option);
	// if (option == 1) {
	//	end_game = 1;
	// }
}

void player_logic(int player_id) {
	render_player(&game_state.players[player_id]);
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

void get_console_size(int *width, int *height) {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	*width = w.ws_col;
	*height = w.ws_row;
}

/**
 * @brief renders a text line in the console
 *
 */
void render_line() {
	// get the console size
	int width, height;
	get_console_size(&width, &height);
	// render the line
	for (int i = 0; i < width; i++) {
		printf("-");
	}
	printf("\n");
}

void render_card(Card *card) {

	// the card holds number and color
	// render the text with the color
	// the joker is white, as normal text
	assert(card != NULL);
	// change the color
	switch (card->color) {
	case RED:
		printf("\033[0;31m");
		break;
	case GREEN:
		printf("\033[0;32m");
		break;
	case BLUE:
		printf("\033[0;34m");
		break;
	case YELLOW:
		printf("\033[0;33m");
		break;
	case JOKER:
		printf("\033[0;37m");
		break;
	default:
		// assert with an error
		assert(0);
		break;
	}
	// render the card if it is not a joker
	if (card->color != JOKER) {
		printf("%d", card->value);
	} else {
		printf("J");
	}
	// reset the color
	printf("\033[0m");
}

void render_hand(Hand *hand) {
	// render the hand
	printf("| ");
	for (int i = 0; i < hand->cards->size; i++) {
		render_card((Card *)hand->cards->data[i]);
		// render the separator
		printf(" | ");
	}
	printf("\n");
}

void render_combinations(Vector *combinations) {
	assert(combinations != NULL);
	for (int i = 0; i < combinations->size; i++) {
		combination_t *combination = (combination_t *)combinations->data[i];
		printf("| ");
		for (int j = 0; j < combination->num_cards; j++) {
			render_card((Card *)combination->cards[j]);
			// render the separator
			printf(" | ");
		}
		printf("\n");
	}
}

/**
 * @brief returns a combination if the movement is valid
 *
 * @param player the player
 * @param combination the combination, with chars with this values (R)ed,
 * (G)reen, (B)lue, (Y)ellow, (J)oker, ( )empty
 * @return combination_t* the combination if the movement is valid, NULL
 * otherwise
 */
combination_t *try_same(Player *player, char combination[4]) {
	assert(player != NULL);
	assert(combination != NULL);
	return NULL;
}

int player_action(Player *player) {
	printf("select your next action\n");
	printf("1. do a move\n");
	printf("2. draw a card\n");
	printf("3. end the game\n");
	int option = 0;
	scanf("%d", &option);
	switch (option) {
	case 1: {
		// the player can do a pair, ladder or mix a card with one in the board
		// also the move can be done with a joker as a wildcard
		// however the moves need to sum at least 30 points
		// if the sum is not 30 points, the player can't do the moves
		// the player can't do the moves if he has no cards left
		// which is an instant win
		int finished = 0;
		// Vector *combinations = new_vector();
		//  contains a list of all the cards that the player cannot select
		// int selected_cards[DECK_MAX_SIZE];
		while (finished == 0) {
			// print the combinations
			render_line();
			// render_line();
			// printf("Your combinations:\n");
			// render_line();
			// render_line();
			// render_combinations(combinations);
			// render_line();
			render_line();
			printf("select the next move type\n");
			printf("1. pair with different color\n");
			printf("2. ladder with same color\n");
			printf("1. combination with a movement on the board\n");
			printf("3. finish movements\n");
			printf("4. cancel\n");
			int move_type = 0;
			scanf("%d", &move_type);
			switch (move_type) {
			// try a movement with same color
			// pick the number and then the color
			case 1: {

			} break;
			}
			return 1;
		}
	} break;
	case 2: {
		// the player can draw a card from the deck
		// the player can't draw a card the game ends
		// Card *card = popCard(&game_state.board.deck);
		// if (card != NULL) {
		//	add_card(player->hand, card);
		//}
		return 1;
	} break;
	case 3: {
		// the player can end the game
		// the game ends
		end_game = 1;
		return 1;
	} break;
	}
	return 0;
}
void render_player(Player *player) {
	assert(player != NULL);
	do {
		clear_screen();
		printf("player : #%d\n", player->id + 1);
		render_line();
		printf("hand : \n");
		render_hand(player->hand);
		render_line();
		printf("board : \n");
		render_board_combinations();
		render_line();
	} while (player_action(player) != 1);
}

void render_board_combinations() {
	Vector *combinations = game_state.board.combinations;
	size_t combinations_size = combinations->size;
	for (int i = 0; i < combinations_size; i++) {
		combination_t *combination = combinations->data[i];
		render_combination(combination);
	}
}

void render_combination(combination_t *combination) {
	assert(combination != NULL);
	printf("- ");
	for (int i = 0; i < combination->num_cards; i++) {
		render_card((Card *)combination->cards[i]);
		// render the separator
		printf(" - ");
	}
	printf("\n");
}
