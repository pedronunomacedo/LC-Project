#include "game_end_menu.h"

#include "assets/game/win_player1.xpm"
#include "assets/game/win_player2.xpm"
#include "assets/game/draw.xpm"

static sprite * win_player1;
static sprite * win_player2;
static sprite * draw;
static int result;

int (initialize_game_end_menu)(void) {
    win_player1 = sprite_new(win_player1_xpm,0,0);
    win_player2 = sprite_new(win_player2_xpm,0,0);
    draw = sprite_new(draw_xpm,0,0);
    result = DRAW;
    if (win_player1 == NULL || 
        win_player2 == NULL ||
        draw == NULL) {
        return !OK;
    }
    return OK;
}

void (destroy_game_end_menu)(void) {
    sprite_destroy(win_player1);
    sprite_destroy(win_player2);
    sprite_destroy(draw);
}

int (draw_game_end_menu)(void) {
    if (result == DRAW) {
        if (vg_draw_block_sprite_without_checks(draw) != OK) { return !OK; }
    } else if (result == PLAYER1) {
        if (vg_draw_block_sprite_without_checks(win_player1) != OK) { return !OK; }
    } else if (result == PLAYER2) {
        if (vg_draw_block_sprite_without_checks(win_player2) != OK) { return !OK; }
    } else { return !OK; }
    return OK;
}

void (set_result_game_end_menu)(int res) {
    result = res;
}
