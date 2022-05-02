#pragma once

#include <lcom/lcf.h>
#include "lib/devices/graphics.h"
#include "lib/sprite/sprite.h"
#include "lib/utils/utils.h"

#define MOUSE_SIDE 30
#define PAUSE_BACK_BTN_X 602
#define PAUSE_BACK_BTN_Y 664
#define CONTINUE_BTN_X 150
#define CONTINUE_BTN_Y 664

int (initialize_pause_menu)(uint32_t x, uint32_t y);

void (destroy_pause_menu)(void);

int (draw_pause_menu)(void);

sprite * get_mouse_sprite_pause_menu();

sprite * get_back_sprite_pause_menu();

sprite * get_continue_sprite_pause_menu();
