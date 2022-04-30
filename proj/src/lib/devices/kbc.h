#pragma once

#include <lcom/lcf.h>
#include "i8042.h"

//keyboard
void (kbd_ih)(void);

int (kbd_subscribe_int)(uint8_t *bit_no);

int (kbd_unsubscribe_int)();

uint8_t (get_keyboard_data)(void);

bool (check_keyboard_error)(void);

//mouse
void (mouse_ih)(void);

int (mouse_subscribe_int)(uint8_t * bit_no);

int (mouse_unsubscribe_int)(void);

int (set_mouse_data_reporting)(bool enable);

uint8_t (get_mouse_data)(void);

bool (check_mouse_error)(void);

struct packet (get_mouse_packet)(uint8_t * mouse_packet);

bool (check_only_rb)(struct packet pp);

bool (check_only_lb)(struct packet pp);

bool ((check_none_pressed))(struct packet pp);

//kbc
int (get_status_register)(uint8_t * st);

void (wait_for_IB_is_clear)();
