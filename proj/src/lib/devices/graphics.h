#pragma once

#include <lcom/lcf.h>
#include <machine/int86.h>
#include <sys/mman.h>

#include "vbe.h"

int (vg_set_video_mode)(uint16_t mode);

void * (vg_init)(uint16_t mode);

int (vg_swap_buffers)();

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (vg_draw_sprite)(uint8_t * sprite, xpm_image_t img, uint16_t x, uint16_t y);

uint32_t (set_bits)(uint8_t start, uint8_t end);

char* (vg_get_current_buffer)();
