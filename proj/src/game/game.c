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
    state->column = 3;
    for (int i = 0; i < 6; i++) for (int j = 0; j < 7; j++) { state->board[i][j] = 0; }
    update_sprite_column();
}

int (draw_game)(void) {
    vg_set_current_buffer(state->display_buffer);
    if (state->turn == 1) {
        if (vg_draw_block_sprite_without_checks(turn_player1) != OK) { return !OK; }
        if (vg_draw_sprite(blue_piece) != OK) { return !OK; }
    } else {
        if (vg_draw_block_sprite_without_checks(turn_player2) != OK) { return !OK; }
        if (vg_draw_sprite(red_piece) != OK) { return !OK; }
    }
    return OK;
}

void (game_set_column_right)(void) {
    if (state->column + 1 == COLUMN_NUM) return;
    state->column += 1;
    update_sprite_column();
}

void (game_set_column_left)(void) {
    if (state->column == 0) return;
    state->column -= 1;
    update_sprite_column();
}

void (update_sprite_column)(void) {
    if (state->turn == 1) {
        sprite_set_pos(blue_piece,game_get_X_pos(state->column),game_get_Y_pos(-1));
    } else {
        sprite_set_pos(red_piece,game_get_X_pos(state->column),game_get_Y_pos(-1));
    }
}

void (game_move)(void) {
    if (state->board[0][state->column] != EMPTY) { return; }
    int col = 0;
    for (int i = 0; i < 6; i++) {
        if (state->board[i][state->column] != 0) {
            state->board[i - 1][state->column] = state->turn;
            col = i - 1;
            break;
        } else if (i == 5) {
            col = 5;
            state->board[5][state->column] = state->turn;
        }
    }

    if (state->turn == 1) {
        sprite_set_pos(blue_piece,
                        game_get_X_pos(state->column),
                        game_get_Y_pos(col));
        vg_draw_sprite_in_buffer(state->display_buffer, blue_piece);
    } else {
        sprite_set_pos(red_piece,
                        game_get_X_pos(state->column),
                        game_get_Y_pos(col));
        vg_draw_sprite_in_buffer(state->display_buffer, red_piece);
    }

    next_turn();
}

void (next_turn)(void) {
    state->turn = (state->turn == 1) ? 2 : 1;
    state->column = 3;
    update_sprite_column();
}
