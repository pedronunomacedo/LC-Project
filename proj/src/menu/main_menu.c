#include "main_menu.h"

#include "../assets/mouse/mouse.xpm"
#include "../assets/main_menu/background.xpm"

static sprite * mouse_sprite;
static sprite * background_sprite;

int (initialize_main_menu)(uint32_t x, uint32_t y) {
    mouse_sprite = sprite_new(mouse_xpm, x, y);
    background_sprite = sprite_new(background_xpm, 0, 0);
    if (mouse_sprite == NULL || background_sprite == NULL) {
        return !OK;
    }
    return OK;
}

int (draw_main_menu)(void) {
    if (vg_draw_sprite_no_checks(background_sprite) != OK) { return !OK; }
    if (vg_draw_sprite(mouse_sprite) != OK) { return !OK; }
    return OK;
}

sprite * get_mouse_sprite_main_menu() { return mouse_sprite; }
