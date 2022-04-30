#pragma once
#include <lcom/lcf.h>

#include "menu/main_menu.h"
#include "lib/sprite/sprite.h"

typedef enum {
    IN_GAME,
    END_GAME,
    MAIN_MENU,
    PAUSE_MENU,
    RULES,
    QUIT,
} GAME_STATE;

GAME_STATE (handle_timer_main_menu)();

GAME_STATE (handle_keyboard_main_menu)(uint16_t scancode);

GAME_STATE (handle_mouse_main_menu)(struct packet pp);
