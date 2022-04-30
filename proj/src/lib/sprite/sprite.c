#include "sprite.h"

sprite * (sprite_new)(xpm_map_t xpm, uint32_t x, uint32_t y) {
    sprite * s = (sprite *)malloc(sizeof(sprite));
    if (s == NULL) return NULL;
    s->map = xpm_load(xpm, XPM_8_8_8_8, &(s->img));
    s->x = x;
    s->y = y;
    return s;
}

void (sprite_destroy)(sprite * sprite) {
    free(sprite->map);
    free(sprite);
}

void (sprite_set_pos)(sprite * sprite, uint8_t x, u_int8_t y) {
    sprite->x = x;
    sprite->y = y;
}

