#pragma once

#include <lcom/lcf.h>
#include <stdint.h>
#include "lib/sprite/sprite.h"

int(util_get_LSB)(uint16_t val, uint8_t *lsb);

int(util_get_MSB)(uint16_t val, uint8_t *msb);

int(util_sys_inb)(int port, uint8_t *value);

bool (check_mouse_in_button)(struct sprite * mouse, struct sprite * button);
