#pragma once

#include <lcom/lcf.h>
#include "i8042.h"

int (mouse_subscribe_int)(uint8_t * bit_no);

int (mouse_unsubscribe_int)(void);

int (set_mouse_data_reporting)(bool enable);

void (mouse_ih)(void);

void (wait_for_IB_is_clear)();

int (get_status_register)(uint8_t * st);

uint8_t (get_mouse_data)(void);

bool (check_mouse_error)(void);

struct packet (get_mouse_packet)(uint8_t * mouse_packet);