#pragma once

#include <lcom/lcf.h>
#include "lib/devices/graphics.h"
#include "lib/sprite/sprite.h"
#include "lib/utils/utils.h"
#include "font.h"

#define MOUSE_SIDE 30
#define BUTTONS_X 376
#define PLAY_BTN_Y 400
#define RULES_BTN_Y 550
#define QUIT_BTN_Y 700

int (initialize_main_menu)(uint32_t x, uint32_t y);

void (destroy_main_menu)(void);

int (draw_main_menu)(void);

sprite * get_mouse_sprite_main_menu();

sprite * get_play_sprite_main_menu();

sprite * get_rules_sprite_main_menu();

sprite * get_quit_sprite_main_menu();
