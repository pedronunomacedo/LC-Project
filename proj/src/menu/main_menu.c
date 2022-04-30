#include "main_menu.h"

#include "../assets/mouse/mouse.xpm"

static sprite * mouse_sprite;

int (initialize_main_menu)(uint32_t x, uint32_t y) {
    mouse_sprite = sprite_new(mouse_xpm, 100, 100);
    if (mouse_sprite == NULL) {
        return !OK;
    }
    return OK;
}

int (draw_main_menu)(void) {
    return vg_draw_sprite(mouse_sprite->map, mouse_sprite->img, mouse_sprite->x, mouse_sprite->y);
}
