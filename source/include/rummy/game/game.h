#pragma once
#include <rummy/game/board.h>

typedef struct{
    Board board;
    
}game_state_t;

void *game_thread_main(void *);
void *player_thread(void *player_id_ptr);