#pragma once

#include <lcom/lcf.h>
#include "lib/sprite/sprite.h"
#include "lib/devices/graphics.h"
#include "game/game_utils.h"

#define COLUMN_NUM 7
#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

typedef struct game
{
    uint8_t board[6][7];
    char * display_buffer;
    int turn;
    int column;
} game;

int (initialize_game)();

void (destroy_game)(void);

void (start_game)(void);

int (draw_game)(void);

void (game_set_column_right)(void);

void (game_set_column_left)(void);

void (update_sprite_column)(void); 

void (game_move)(void);

void (next_turn)(void);
