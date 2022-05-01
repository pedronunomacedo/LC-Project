#include "events.h"

GAME_STATE (handle_timer_main_menu)() {
    if (draw_main_menu() == OK) {
        vg_swap_buffers();
    }
    return MAIN_MENU;
}

GAME_STATE (handle_keyboard_main_menu)(uint16_t scancode) {
    if (scancode == 0x81) {
        return QUIT;
    }
    return MAIN_MENU;
}

GAME_STATE (handle_mouse_main_menu)(struct packet pp) {
    sprite_set_pos_delta(get_mouse_sprite_main_menu(), pp.delta_x, pp.delta_y);
    if (pp.lb) {
        if (check_mouse_in_button(get_quit_sprite_main_menu())) {
            return QUIT;
        }
    }
    return MAIN_MENU;
}
