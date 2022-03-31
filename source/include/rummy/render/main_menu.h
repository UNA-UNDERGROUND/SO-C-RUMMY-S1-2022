#pragma once


typedef enum{
    NEW_GAME = 1,
    EXIT_GAME = 2,
    INVALID_OPTION,
} OPT_MAIN_MENU;

OPT_MAIN_MENU render_main_menu();