#include <rummy/render/main_menu.h>
// windows define so we can use the same code on windows and linux
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

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