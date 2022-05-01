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
    struct sprite * mouse = get_mouse_sprite_main_menu();
    sprite_set_pos_delta(mouse, pp.delta_x, pp.delta_y);
    if (pp.lb) {
        if (check_mouse_in_button(mouse, get_quit_sprite_main_menu())) {
            return QUIT;
        } else if (check_mouse_in_button(mouse, get_rules_sprite_main_menu())) {
            sprite_set_pos(get_mouse_sprite_rules_menu(), mouse->x, mouse->y);
            return RULES_MENU;
        }
    }
    return MAIN_MENU;
}

GAME_STATE (handle_timer_rules_menu)() {
    if (draw_rules_menu() == OK) {
        vg_swap_buffers();
    }
    return RULES_MENU;
}

GAME_STATE (handle_keyboard_rules_menu)(uint16_t scancode) {
    if (scancode == 0x81) {
        return MAIN_MENU;
    }
    return RULES_MENU;
}

GAME_STATE (handle_mouse_rules_menu)(struct packet pp) {
    struct sprite * mouse = get_mouse_sprite_rules_menu();
    sprite_set_pos_delta(get_mouse_sprite_rules_menu(), pp.delta_x, pp.delta_y);
    if (pp.lb) {
        if (check_mouse_in_button(get_mouse_sprite_rules_menu(), get_back_sprite_rules_menu())) {
            sprite_set_pos(get_mouse_sprite_main_menu(), mouse->x, mouse->y);
            return MAIN_MENU;
        }
    }
    return RULES_MENU;
}
