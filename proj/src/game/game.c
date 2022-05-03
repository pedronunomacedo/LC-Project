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
    state->turn = PLAYER1;
    state->column = COLUMN_CENTER;
    for (int i = 0; i < ROW_NUM; i++) 
        for (int j = 0; j < COLUMN_NUM; j++) { state->board[i][j] = 0; }
    update_sprite_column();
}

int (draw_game)(void) {
    vg_set_current_buffer(state->display_buffer);
    if (state->turn == PLAYER1) {
        if (vg_draw_block_sprite_without_checks(turn_player1) != OK) { return !OK; }
        if (vg_draw_sprite(blue_piece) != OK) { return !OK; }
    } else if (state->turn == PLAYER2) {
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
    if (state->turn == PLAYER1) {
        sprite_set_pos(blue_piece,game_get_X_pos(state->column),game_get_Y_pos(-1));
    } else if (state->turn == PLAYER2) {
        sprite_set_pos(red_piece,game_get_X_pos(state->column),game_get_Y_pos(-1));
    }
}

int (game_move)() {
    if (state->board[0][state->column] != EMPTY) { return 0; }
    int winner, col = 0;
    for (int i = 0; i < ROW_NUM; i++) {
        if (state->board[i][state->column] != 0) {
            state->board[i - 1][state->column] = state->turn;
            col = i - 1;
            break;
        } else if (i == ROW_NUM - 1) {
            col = ROW_NUM - 1;
            state->board[ROW_NUM - 1][state->column] = state->turn;
        }
    }

    if (state->turn == PLAYER1) {
        sprite_set_pos(blue_piece,
                        game_get_X_pos(state->column),
                        game_get_Y_pos(col));
        vg_draw_sprite_in_buffer(state->display_buffer, blue_piece);
    } else if (state->turn == PLAYER2) {
        sprite_set_pos(red_piece,
                        game_get_X_pos(state->column),
                        game_get_Y_pos(col));
        vg_draw_sprite_in_buffer(state->display_buffer, red_piece);
    }

    if ((winner = check_game_end()) != 0) { return winner; }

    next_turn();
    return 0;
}

void (next_turn)(void) {
    state->turn = (state->turn == PLAYER1) ? PLAYER2 : PLAYER1;
    state->column = COLUMN_CENTER;
    update_sprite_column();
}

int (check_game_end)() {
    int counter = 0;
    for (int i = 0; i < ROW_NUM; i++) {
        counter = 0;
        for (int j = 0; j < COLUMN_NUM; j++) {
            if (state->board[i][j] == state->turn) {
                counter++;
                if (counter == 4) { return state->turn; }
            } else { counter = 0; }
        }
    }

    for (int j = 0; j < COLUMN_NUM; j++) {
        counter = 0;
        for (int i = 0; i < ROW_NUM; i++) {
            if (state->board[i][j] == state->turn) {
                counter++;
                if (counter == 4) { return state->turn; }
            } else { counter = 0; }
        }
    }
    //only first and last row (it is enough)
    for (int i = 0; i < ROW_NUM; i+=ROW_NUM-1) {
        for (int j = 0; j < COLUMN_NUM; j++) {
            counter = 0;
            //right-down
            for (int ii = i, jj = j; 
                    ii < ROW_NUM || jj < COLUMN_NUM;
                    ii++,jj++) {
                if (state->board[ii][jj] == state->turn) {
                    counter++;
                    if (counter == 4) { return state->turn; }
                } else { counter = 0; }
            }
            counter = 0;
            //right-up
            for (int ii = i, jj = j; 
                    ii >= 0 || jj < COLUMN_NUM;
                    ii--,jj++) {
                if (state->board[ii][jj] == state->turn) {
                    counter++;
                    if (counter == 4) { return state->turn; }
                } else { counter = 0; }
            }
            counter = 0;
            //left-down
            for (int ii = i, jj = j; 
                    ii < ROW_NUM || jj >= 0;
                    ii++,jj--) {
                if (state->board[ii][jj] == state->turn) {
                    counter++;
                    if (counter == 4) { return state->turn; }
                } else { counter = 0; }
            }
            counter = 0;
            //left-up
            for (int ii = i, jj = j; 
                    ii >= 0 || jj >= 0;
                    ii--,jj--) {
                if (state->board[ii][jj] == state->turn) {
                    counter++;
                    if (counter == 4) { return state->turn; }
                } else { counter = 0; }
            }
        }
    }

    return 0;
}
