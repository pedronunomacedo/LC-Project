#pragma once

#include <lcom/lcf.h>

#define DELAY_US 20000

#define KBD_ESQ_BC 0x81 // ESQ breakcode
#define KBD_TWOBYTE_CODE 0xE0 // first byte of a two byte scancode
#define KBD_MSB BIT(7) // MSB of a bit

#define KBD_IRQ 1 // Keyboard irq line number


/* PC Keyboard Operation: Data Input */
#define KBD_STAT_REG 0x64 // Keyboard Status Register
#define KBD_OUT_BUF 0x60 // Keyboard Output Buffer

/* Status Register */
#define KBD_OBF BIT(0) // Output Buffer Full - data available for reading
#define KBD_IBF BIT(1) // Input Buffer - don't write commands or arguments
#define KBD_SYS BIT(2) // System Flag - irrelevant for LCOM
#define KBD_A2 BIT(3) // A2 input line - irrelevant to LCOM
#define KBD_INH BIT(4) // Inhibit flag - 0 if keyboard is inhibited
#define KBD_AUX BIT(5) // Mouse data
#define KBD_TIMEOUT_ERR BIT(6) // Timeout error - invalid data
#define KBD_PARITY_ERR BIT(7) // Parity error - invalid data

/* The KBC Commands */
#define KBC_CMD_RCB 0x20 // Read Command Byte - Returns Command Byte
#define KBC_CMD_WCB 0x60 // Write Command Byte - Takes an argument: Command Byte
#define KBC_CMD_KBC 0xAA // Check KBC (Self-test) - Returns 0x55, if OK
                                                // Returns 0xFC, if error
#define KBC_KBI 0xAB // Check KBD Interface - Returns 0, if OK
#define KBC_DIS_KBDI 0xAD // Disable KBD Interface
#define LBC_EN_KBDI 0xAE // Enable KBD Interface
