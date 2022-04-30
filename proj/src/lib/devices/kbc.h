#pragma once

#include <lcom/lcf.h>
#include "i8042.h"

//keyboard
void (kbd_ih)(void);

int (kbd_subscribe_int)(uint8_t *bit_no);

int (kbd_unsubscribe_int)();

uint16_t (get_keyboard_scancode)(void);

bool (check_keyboard_ready)(void);

//mouse
void (mouse_ih)(void);

bool (check_mouse_ready)(void);

int (mouse_subscribe_int)(uint8_t * bit_no);

int (mouse_unsubscribe_int)(void);

int (set_mouse_data_reporting)(bool enable);

struct packet (get_mouse_packet)();

//kbc
int (get_status_register)(uint8_t * st);

void (wait_for_IB_is_clear)();
