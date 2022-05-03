#pragma once

#include <lcom/lcf.h>
#include "lib/devices/graphics.h"
#include "lib/sprite/sprite.h"
#include "lib/utils/utils.h"
#include "game/game.h"

int (initialize_game_end_menu)(void);

void (destroy_game_end_menu)(void);

int (draw_game_end_menu)(void);

void (set_result_game_end_menu)(int res);
