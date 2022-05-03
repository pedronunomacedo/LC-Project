#pragma once

#include <lcom/lcf.h>
#include <machine/int86.h>
#include <sys/mman.h>

#include "vbe.h"
#include "../sprite/sprite.h"

int (vg_set_video_mode)(uint16_t mode);

void * (vg_init)(uint16_t mode);

int (vg_swap_buffers)();

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (vg_draw_pixel_in_buffer)(char * buffer, uint16_t x, uint16_t y, uint32_t color);

int (vg_draw_sprite)(struct sprite * sprite);

int (vg_draw_sprite_in_buffer)(char * buffer, struct sprite * sprite);

int (vg_draw_block_sprite_without_checks)(struct sprite * sp);

void (vg_set_current_buffer)(char * buffer);

unsigned int (vg_get_vram_size)();
