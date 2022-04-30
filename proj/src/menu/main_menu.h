#pragma once

#include <lcom/lcf.h>
#include "lib/devices/graphics.h"
#include "lib/sprite/sprite.h"

int (initialize_main_menu)(uint32_t x, uint32_t y);

int (draw_main_menu)(void);

sprite * get_mouse_sprite();
