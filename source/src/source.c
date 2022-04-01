#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <rummy/game/game.h>
#include <rummy/render/main_menu.h>
#include <stdio.h>

int main() {
	while (1) {
		OPT_MAIN_MENU option = render_main_menu();
		switch (option) {
		case NEW_GAME:
			// launch the game thread
			pthread_t game_thread;
			pthread_t player_threads[4];
			int player_ids[4];
			pthread_create(&game_thread, NULL, game_thread_main, NULL);
			for (int i = 0; i < 4; i++) {
				player_ids[i] = i;
				pthread_create(&player_threads[i], NULL, player_thread,
				               &player_ids[i]);
			}
			pthread_join(game_thread, NULL);
			// join the player threads
			for (int i = 0; i < 4; i++) {
				pthread_join(player_threads[i], NULL);
			}
			break;
		case EXIT_GAME:
			return 0;
		default:
			continue;
		}
	}
}