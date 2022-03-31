#include <rummy/render/main_menu.h>

int main() {
	while (1) {
		OPT_MAIN_MENU option = render_main_menu();
		switch (option) {
		case EXIT_GAME:
			return 0;
		default:
			continue;
		}
	}
}