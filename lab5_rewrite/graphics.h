#pragma once

#include <lcom/lcf.h>
#include <machine/int86.h>

#define VBE_AH 0x4f
#define VBE_INT_NO 0x10
#define VBE_SET_VIDEO_MODE 0x02

int (vg_set_mode)(uint16_t mode);

int (vg_init_graphics)(uint16_t mode);

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

int (vg_draw_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step);

int (vg_draw_sprite)(unsigned char* sprite, xpm_image_t img,uint16_t x, uint16_t y);

uint32_t set_bits(uint32_t n);
