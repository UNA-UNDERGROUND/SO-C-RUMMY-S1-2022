#pragma once
#include <rummy/game/board.h>
#include <rummy/game/player.h>

typedef struct{
    Board board;
    Player players[4];
}game_state_t;

void *game_thread_main(void *);
void *player_thread(void *player_id_ptr);