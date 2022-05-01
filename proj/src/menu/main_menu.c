#include "main_menu.h"

#include "../assets/mouse/mouse.xpm"
#include "../assets/main_menu/background.xpm"
#include "../assets/main_menu/play_button.xpm"
#include "../assets/main_menu/play_button_hover.xpm"
#include "../assets/main_menu/rules_button.xpm"
#include "../assets/main_menu/rules_button_hover.xpm"
#include "../assets/main_menu/quit_button.xpm"
#include "../assets/main_menu/quit_button_hover.xpm"

static sprite * mouse_sprite;
static sprite * background_sprite;
static sprite * play_button;
static sprite * play_button_hover;
static sprite * rules_button;
static sprite * rules_button_hover;
static sprite * quit_button;
static sprite * quit_button_hover;

int (initialize_main_menu)(uint32_t x, uint32_t y) {
    mouse_sprite = sprite_new(mouse_xpm, x - 30, y + 30);
    background_sprite = sprite_new(background_xpm, 0, 0);
    play_button = sprite_new(play_button_xpm, 376, 400);    
    play_button_hover = sprite_new(play_button_hover_xpm, 376, 400);
    rules_button = sprite_new(rules_button_xpm, 376, 550);    
    rules_button_hover = sprite_new(rules_button_hover_xpm, 376, 550);
    quit_button = sprite_new(quit_button_xpm, 376, 700);    
    quit_button_hover = sprite_new(quit_button_hover_xpm, 376, 700);
    if (mouse_sprite == NULL || 
        background_sprite == NULL ||
        play_button == NULL || 
        play_button_hover == NULL ||
        rules_button == NULL || 
        rules_button_hover == NULL ||
        quit_button == NULL || 
        quit_button_hover == NULL) {
        return !OK;
    }
    return OK;
}

void (destroy_main_menu)(void) {
    sprite_destroy(mouse_sprite);
    sprite_destroy(background_sprite);
    sprite_destroy(play_button);    
    sprite_destroy(play_button_hover);
    sprite_destroy(rules_button);    
    sprite_destroy(rules_button_hover);
    sprite_destroy(quit_button);    
    sprite_destroy(quit_button_hover);
}

int (draw_main_menu)(void) {
    if (vg_draw_sprite_no_checks(background_sprite) != OK) { return !OK; }

    if (check_mouse_in_button(play_button)) {
        if (vg_draw_sprite_no_checks(play_button_hover) != OK) { return !OK; }
    } else {
        if (vg_draw_sprite_no_checks(play_button) != OK) { return !OK; }
    }

    if (check_mouse_in_button(rules_button)) {
        if (vg_draw_sprite_no_checks(rules_button_hover) != OK) { return !OK; }
    } else {
        if (vg_draw_sprite_no_checks(rules_button) != OK) { return !OK; }
    }

    if (check_mouse_in_button(quit_button)) {
        if (vg_draw_sprite_no_checks(quit_button_hover) != OK) { return !OK; }
    } else {
        if (vg_draw_sprite_no_checks(quit_button) != OK) { return !OK; }
    }
    if (vg_draw_sprite(mouse_sprite) != OK) { return !OK; }
    return OK;
}

bool (check_mouse_in_button)(struct sprite * button) {
    return  mouse_sprite->x > button->x && 
            mouse_sprite->x < button->x + button->img.width &&
            mouse_sprite->y > button->y &&
            mouse_sprite->y < button->y + button->img.height;
}

sprite * get_mouse_sprite_main_menu() { return mouse_sprite; }

sprite * get_play_sprite_main_menu() { return play_button; }

sprite * get_rules_sprite_main_menu() { return rules_button; }

sprite * get_quit_sprite_main_menu() { return quit_button; }
