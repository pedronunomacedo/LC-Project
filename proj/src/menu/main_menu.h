#pragma once

#include <lcom/lcf.h>
#include "lib/devices/graphics.h"
#include "lib/sprite/sprite.h"

#define BUTTONS_HEIGHT 100;

int (initialize_main_menu)(uint32_t x, uint32_t y);

void (destroy_main_menu)(void);

int (draw_main_menu)(void);

bool (check_mouse_in_button)(struct sprite * button);

sprite * get_mouse_sprite_main_menu();
