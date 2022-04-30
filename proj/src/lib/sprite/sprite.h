#pragma once
#include <lcom/lcf.h>

#define WINDOW_WIDTH 1152
#define WINDOW_HEIGHT 864

typedef struct sprite
{
    uint8_t * map;
    xpm_image_t img;
    uint32_t x;
    uint32_t y;
} sprite;

sprite * (sprite_new)(xpm_map_t xpm, uint32_t x, uint32_t y);

void (sprite_destroy)(sprite * sprite);

void (sprite_set_pos)(sprite * sprite, uint32_t x, uint32_t y);

void (sprite_set_pos_delta)(sprite * sprite, int x_delta, int y_delta);
