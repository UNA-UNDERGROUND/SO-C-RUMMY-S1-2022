#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <rummy/game/game.h>
#include <sched.h>
#include <stdio.h>

pthread_mutex_t game_mutex;
pthread_cond_t game_thread_ready;
pthread_cond_t player_thread_ready;
int game_thread_ready_flag = 0;
int player_thread_ready_flag = 0;
int actual_player_id = 0;
int end_game;

void *game_thread_main(void *ptr) {
	// set/reset the game flags
	end_game = 0;
	actual_player_id = 0;
    player_thread_ready_flag = 0;
	// do game initialization
	// end of game initialization
	while (end_game == 0) {
		// set the game thread ready flag
		game_thread_ready_flag = 0;
		pthread_cond_signal(&game_thread_ready);
		// game logic
		printf("game thread main\n");
		// ask if want to end game
		int option = 0;
		printf("Do you want to end the game?\n");
		printf("1. Yes\n");
		printf("2. No\n");
		scanf("%d", &option);
		if (option == 1) {
			end_game = 1;
			continue;
		}
		// end of game logic
		// let the players threads know that the game is ready
		game_thread_ready_flag = 1;
		pthread_cond_signal(&game_thread_ready);
		// wait until the next player finishes
		while (player_thread_ready_flag == 0) {
			pthread_cond_wait(&player_thread_ready, &game_mutex);
		}
		// reset the player thread ready flag
		player_thread_ready_flag = 0;
		// update the actual player id
		actual_player_id = (actual_player_id + 1) % 4;
	}
	// game thread unitialization
	// end of game unitialization
	// reset the initialized flag
	game_thread_ready_flag = 0;
	return 0;
}
void *player_thread(void *player_id_ptr) {
	int player_id = *((int *)player_id_ptr);
	// before starting wait until the game thread is ready
	// using a condition variable

	while (game_thread_ready_flag == 0) {
		pthread_cond_wait(&game_thread_ready, &game_mutex);
	}
	while (end_game == 0) {
		// wait until the game thread is ready and is the actual player
		while (game_thread_ready_flag == 0 || actual_player_id != player_id) {
			pthread_cond_wait(&game_thread_ready, &game_mutex);
		}
		// init player logic
		printf("player : %d thread\n", player_id);
		// end of player logic - set the player thread ready flag
		player_thread_ready_flag = 1;
        game_thread_ready_flag = 0;
		pthread_cond_signal(&game_thread_ready);
        pthread_cond_signal(&player_thread_ready);
	}
	return 0;
}