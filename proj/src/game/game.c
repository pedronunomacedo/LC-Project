#include "game.h"

#include "assets/game/board.xpm"
#include "assets/game/turn_player1.xpm"
#include "assets/game/turn_player2.xpm"
#include "assets/game/pieces/blue_piece.xpm"
#include "assets/game/pieces/red_piece.xpm"

static game * state;
static sprite * board;
static sprite * turn_player1;
static sprite * turn_player2;
static sprite * blue_piece;
static sprite * red_piece;

int (initialize_game)() {
    state = (game *)malloc(sizeof(game));
    if (state == NULL) { return !OK; }

    board = sprite_new(board_xpm,0,0);
    state->display_buffer = (char *)malloc(vg_get_vram_size());
    if (state->display_buffer == NULL) {
        return !OK;
    }

    turn_player1 = sprite_new(turn_player1_xpm,862,15);
    turn_player2 = sprite_new(turn_player2_xpm,862,15);
    blue_piece = sprite_new(blue_piece_xpm,0,0);
    red_piece = sprite_new(red_piece_xpm,0,0);
    if (board == NULL ||
        turn_player1 == NULL ||
        turn_player2 == NULL) {
        return !OK;
    }
    return OK;
}

void (destroy_game)(void) {
    sprite_destroy(board);
    sprite_destroy(turn_player1);
    sprite_destroy(turn_player2);
    sprite_destroy(blue_piece);
    sprite_destroy(red_piece);
    free(state->display_buffer);
    free(state);
}

void (start_game)(void) {
    memcpy(state->display_buffer, board->map, vg_get_vram_size());
    state->turn = 1;
    state->column = 0;
    for (int i = 0; i < 6; i++) for (int j = 0; j < 7; j++) { state->board[i][j] = 0; }
    sprite_set_pos(blue_piece,game_get_X_pos(0),game_get_Y_pos(0));
    sprite_set_pos(red_piece,game_get_X_pos(0),game_get_Y_pos(0));
}

int (draw_game)(void) {
    vg_set_current_buffer(state->display_buffer);
    if (state->turn == 1) {
        if (vg_draw_block_sprite_without_checks(turn_player1) != OK) { return !OK; }
    } else {
        if (vg_draw_block_sprite_without_checks(turn_player2) != OK) { return !OK; }
    }
    sprite_set_pos(blue_piece,game_get_X_pos(state->column),game_get_Y_pos(0));
    vg_draw_sprite(blue_piece);
    return OK;
}

void (game_set_column_right)(void) {
    if (state->column + 1 == COLUMN_NUM) return;
    state->column += 1;
}

void (game_set_column_left)(void) {
    if (state->column == 0) return;
    state->column -= 1;
}

