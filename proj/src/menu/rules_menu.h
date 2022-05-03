#pragma once

#include <lcom/lcf.h>
#include "lib/devices/graphics.h"
#include "lib/sprite/sprite.h"
#include "lib/utils/utils.h"
#include "font.h"

#define MOUSE_SIDE 30
#define BACK_BTN_X 652
#define BACK_BTN_Y 664

int (initialize_rules_menu)(uint32_t x, uint32_t y);

void (destroy_rules_menu)(void);

int (draw_rules_menu)(void);

sprite * get_mouse_sprite_rules_menu();

sprite * get_back_sprite_rules_menu();
