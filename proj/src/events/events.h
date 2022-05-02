#pragma once
#include <lcom/lcf.h>

#include "game/game.h"
#include "menu/main_menu.h"
#include "menu/rules_menu.h"
#include "lib/sprite/sprite.h"

typedef enum {
    IN_GAME,
    END_GAME,
    MAIN_MENU,
    PAUSE_MENU,
    RULES_MENU,
    QUIT,
} GAME_STATE;

GAME_STATE (handle_timer_main_menu)();

GAME_STATE (handle_keyboard_main_menu)(uint16_t scancode);

GAME_STATE (handle_mouse_main_menu)(struct packet pp);

GAME_STATE (handle_timer_rules_menu)();

GAME_STATE (handle_keyboard_rules_menu)(uint16_t scancode);

GAME_STATE (handle_mouse_rules_menu)(struct packet pp);

GAME_STATE (handle_timer_game)();

GAME_STATE (handle_keyboard_game)(uint16_t scancode);

GAME_STATE (handle_mouse_game)(struct packet pp);
