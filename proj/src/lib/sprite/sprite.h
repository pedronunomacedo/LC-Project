#pragma once
#include <lcom/lcf.h>

typedef struct sprite
{
    uint8_t * map;
    xpm_image_t img;
    uint32_t x;
    uint32_t y;
} sprite;

sprite * (sprite_new)(xpm_map_t xpm, uint32_t x, uint32_t y);

void (sprite_destroy)(sprite * sprite);

void (sprite_set_pos)(sprite * sprite, uint8_t x, u_int8_t y);
