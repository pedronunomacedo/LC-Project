#pragma once

#include <lcom/lcf.h>

#define MOUSE_IRQ 12

#define KBC_OUT_BUF 0x60
#define KBC_WRITE_ARGS 0x60
#define KBC_READ_ST_REG 0x64
#define KBC_CTRL_REG 0x64

#define KBC_READ_BYTE_CMD 0x20
#define KBC_WRITE_BYTE_CMD 0x60
#define KBC_WRITE_BYTE_MOUSE 0xd4
#define KBC_ENABLE_MOUSE_DATA_REPORTING 0xf4
#define KBC_DISABLE_MOUSE_DATA_REPORTING 0xf5

int (mouse_subscribe_int)(uint8_t * bit_no);

int (mouse_unsubscribe_int)();

int (set_mouse_data_reporting)(bool enable);

int (get_status_register)(uint8_t * st);

void (mouse_ih)(void);

uint8_t get_mouse_data();

bool check_mouse_error();

int assemble_mouse_packet(uint8_t *mouse_data, struct packet *pp);
