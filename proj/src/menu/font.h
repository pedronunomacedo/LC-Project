#pragma once

#include <lcom/lcf.h>
#include "lib/devices/graphics.h"
#include "lib/sprite/sprite.h"
#include "lib/utils/utils.h"
#include "lib/devices/rtc.h"

#define FIRST_X 306
#define FIRST_Y 25
#define NUM_WIDTH 30
#define DATE_SEP_WIDTH 30
#define TIME_SEP_WIDTH 15

int (initialize_font)(void);

void (destroy_font)(void);

int (draw_date_font)(void);

sprite * (get_sprite_font)(char c);
