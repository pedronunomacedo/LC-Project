#pragma once

#include <lcom/lcf.h>

#define KBD_ESQ_BC 0x81
#define KBD_TWOBYTE_CODE 0xE0
#define KBD_MSB BIT(7)

#define KBD_IRQ 1

#define KBC_ST_REG 0x64
#define KBC_OBF BIT(0)
#define KBC_PARITY_ERR BIT(7)
#define KBC_TIMEOUT_ERR BIT(6)

#define KBC_CMD_REG 0x64

#define KBC_OUT_BUF 0x60

#define KBC_CMD_RCB 0x20
#define KBC_CMD_WCB 0x60
