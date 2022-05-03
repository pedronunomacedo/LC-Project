#pragma once

#include <lcom/lcf.h>
#include "lib/sprite/sprite.h"
#include "lib/devices/graphics.h"
#include "game/game_utils.h"

#define COLUMN_NUM 7
#define COLUMN_CENTER 3
#define ROW_NUM 6
#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2
#define DRAW 3
#define ANIMATION_DELTA 15

typedef struct game
{
    uint8_t board[6][7];
    char * display_buffer;
    int turn;
    int column;
} game;

typedef struct anim
{
    sprite * sp;
    int start_x;
    int start_y;
    int final_y;
} anim;

int (initialize_game)();

void (destroy_game)(void);

void (start_game)(void);

int (draw_game)(void);

int (draw_animation_game)(void);

void (game_set_column_right)(void);

void (game_set_column_left)(void);

void (update_sprite_column)(void); 

int (game_move)();

void (game_start_animation)(sprite * sp, int row);

void (next_turn)(void);

int (check_game_end)();

bool (check_animation_game_end)(void);
