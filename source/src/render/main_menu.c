// windows define so we can use the same code on windows and linux
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
// game includes
#include <rummy/render/main_menu.h>
#include <rummy/render/render.h>

OPT_MAIN_MENU render_main_menu() {
    clear_screen();
	printf("Main Menu\n");
	printf("1. New Game\n");
	printf("2. Exit\n");
	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);
	// check if the input is valid
	if (choice < 1 || choice > 2) {
		printf("Invalid choice.\n");
		return INVALID_OPTION;
	}
	return (OPT_MAIN_MENU)choice;
}