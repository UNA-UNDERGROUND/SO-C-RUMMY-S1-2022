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
			pthread_create(&game_thread, NULL, game_thread_main, NULL);
			pthread_join(game_thread, NULL);

			break;
		case EXIT_GAME:
			return 0;
		default:
			continue;
		}
	}
}